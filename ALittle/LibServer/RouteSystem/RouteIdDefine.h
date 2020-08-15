
#ifndef _ALITTLE_ROUTEIDDEFINE_H_
#define _ALITTLE_ROUTEIDDEFINE_H_

#include "ALittle/LibCommon/Helper/StringHelper.h"

typedef unsigned char ROUTE_TYPE;
typedef unsigned char ROUTE_NUM;
typedef unsigned short ROUTE_ID;
typedef unsigned int CONNECT_KEY;

// t：路由类型，n：在t类型下的编号
#define CALC_ROUTE_ID(t, n) ((t << 8) | n)

class RouteIdDefine
{
public:
	// src_route_id：路由ID开始端，dst_route_id：路由ID结束端
	inline static unsigned int CalcConnectKey(unsigned short src_route_id, unsigned short dst_route_id)
	{
		return (((unsigned int)src_route_id) << 16) | dst_route_id;
	}
	// route_id：路由ID
	inline static unsigned char CalcRouteType(unsigned short route_id)
	{
		return route_id >> 8;
	}
	// route_id：路由编号
	inline static unsigned char CalcRouteNum(unsigned short route_id)
	{
		return route_id & 0x00FF;
	}
	// route_type：路由类型
	// route_num：路由编号
	inline static unsigned short CalcRouteId(unsigned char route_type, unsigned char route_num)
	{
		return (((short)route_type) << 8) | route_num;
	}

	// 计算路由信息
	inline static std::string CalcRouteName(unsigned short route_id)
	{
		unsigned short route_type = CalcRouteType(route_id);
		unsigned short route_num = CalcRouteNum(route_id);
		return X2S(route_type) + "_" + X2S(route_num);
	}

	// 计算连接信息
	inline static std::string CalcConnectName(unsigned int connect_key)
	{
		unsigned int src_route_id = connect_key >> 16;
		unsigned int dst_route_id = connect_key & 0x0000ffff;
		return CalcRouteName(src_route_id) + "->" + CalcRouteName(dst_route_id);
	}

}; // RouteIdDefine

#define ROUTE2S(route_id) RouteIdDefine::CalcRouteName(route_id)
#define CONNECT2S(connect_key) RouteIdDefine::CalcConnectName(connect_key)

#endif // _ALITTLE_ROUTEIDDEFINE_H_
