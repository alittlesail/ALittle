#ifndef DEEPLEARNING_DARKNET_INCLUDED
#define DEEPLEARNING_DARKNET_INCLUDED

#include "darknet/include/darknet.h"
#include "carp_lua.hpp"
#include "carp_surface.hpp"

class DeeplearningYolov3
{
public:
    ~DeeplearningYolov3()
    {
        if (m_net) free_network_ptr(m_net);
    }

public:
    bool Load(const char* cfg, const char* weight)
    {
        if (m_net)
        {
            free_network_ptr(m_net);
            m_net = nullptr;
        }
        m_net = load_network((char*)cfg, (char*)weight, 1);
        return m_net != nullptr;
    }

    int Predict(lua_State* l_state)
    {
        if (m_net == nullptr) return 0;

        // »ñÈ¡surface
        size_t surface_address = luaL_checkinteger(l_state, 2);
        CarpSurface* surface = nullptr;
        memcpy(&surface, &surface_address, sizeof(size_t));
        if (surface == nullptr) return 0;

        int letter_box = 0;
        if (m_net->letter_box) letter_box = 1;

        image im = make_image(surface->GetWidth(), surface->GetHeight(), m_net->c);
        auto* data = (const char*)surface->GetPixels();
        for (int k = 0; k < im.c; ++k) {
            for (int j = 0; j < im.h; ++j) {
                for (int i = 0; i < im.w; ++i) {
                    int dst_index = i + im.w * j + im.w * im.h * k;
                    int src_index = k + 4 * i + 4 * im.w * j;
                    im.data[dst_index] = data[src_index] / 255.0f;
                }
            }
        }

        layer l = m_net->layers[m_net->n - 1];
        for (int k = 0; k < m_net->n; ++k) {
            layer lk = m_net->layers[k];
            if (lk.type == YOLO || lk.type == GAUSSIAN_YOLO || lk.type == REGION) {
                l = lk;
            }
        }

        image sized;
        if (letter_box) sized = letterbox_image(im, m_net->w, m_net->h);
        else sized = resize_image(im, m_net->w, m_net->h);

        network_predict_ptr(m_net, sized.data);

        float thresh = 0.24f;
        float hier_thresh = 0.5f;
        float nms = .45f;    // 0.4F
        int nboxes = 0;
        detection* dets = get_network_boxes(m_net, im.w, im.h, thresh, hier_thresh, 0, 1, &nboxes, letter_box);
        if (nms)
        {
            if (l.nms_kind == DEFAULT_NMS) do_nms_sort(dets, nboxes, l.classes, nms);
            else diounms_sort(dets, nboxes, l.classes, nms, l.nms_kind, l.beta_nms);
        }

        lua_newtable(l_state);
        for (int i = 0; i < nboxes; ++i)
        {
            lua_newtable(l_state);

            auto& det = dets[i];
            auto& b = det.bbox;

            int left = (int)((b.x - b.w / 2.) * im.w);
            int right = (int)((b.x + b.w / 2.) * im.w);
            int top = (int)((b.y - b.h / 2.) * im.h);
            int bottom = (int)((b.y + b.h / 2.) * im.h);

            if (left < 0) left = 0;
            if (right > im.w - 1) right = im.w - 1;
            if (top < 0) top = 0;
            if (bottom > im.h - 1) bottom = im.h - 1;

            lua_pushinteger(l_state, left);
            lua_setfield(l_state, -2, "x");
            lua_pushinteger(l_state, top);
            lua_setfield(l_state, -2, "y");
            lua_pushinteger(l_state, right - left);
            lua_setfield(l_state, -2, "w");
            lua_pushinteger(l_state, bottom - top);
            lua_setfield(l_state, -2, "h");

            int best_class = -1;
            float best_class_prob = thresh;
            for (int index = 0; index < dets[i].classes; ++index)
            {
                if (dets[i].prob[index] > best_class_prob)
                {
                    best_class = index;
                    best_class_prob = dets[i].prob[index];
                }
            }
            lua_pushinteger(l_state, best_class);
            lua_setfield(l_state, -2, "clazz");

            lua_rawseti(l_state, -2, i + 1);
        }

        free_detections(dets, nboxes);
        free_image(im);
        free_image(sized);

        return 1;
    }

private:
    network* m_net = nullptr;
};

#endif