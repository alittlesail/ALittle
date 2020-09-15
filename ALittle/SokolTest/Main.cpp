
#define SOKOL_IMPL
#define SOKOL_D3D11
#define SOKOL_WIN32_FORCE_MAIN
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_fetch.h"

sg_pass_action pass_action;

void init(void) {
    sg_desc desc = { 0 };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);

    sg_pass_action pass_action = { 0 };
    pass_action.colors[0].action = SG_ACTION_CLEAR;
    pass_action.colors[0].val[0] = 1.0f;
    pass_action.colors[0].val[0] = 0.0f;
    pass_action.colors[0].val[0] = 0.0f;
    pass_action.colors[0].val[0] = 1.0f;
}

void frame(void) {
    float g = pass_action.colors[0].val[1] + 0.01f;
    pass_action.colors[0].val[1] = (g > 1.0f) ? 0.0f : g;
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    sg_shutdown();
}

void handleevent(const sapp_event* e) {
    if (e->type == SAPP_EVENTTYPE_CHAR)
    {
        printf("char_code %d, key_code %d\n", e->char_code, e->key_code);
    }
}

sapp_desc sokol_main(int argc, char* argv[]) {
    sapp_desc desc = { 0 };
    desc.init_cb = init;
    desc.frame_cb = frame;
    desc.cleanup_cb = cleanup;
    desc.event_cb = handleevent;
    return desc;
}