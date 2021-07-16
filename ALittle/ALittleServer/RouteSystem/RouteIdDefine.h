
#ifndef _ALITTLE_ROUTEIDDEFINE_H_
#define _ALITTLE_ROUTEIDDEFINE_H_

#include <string>

typedef unsigned short ROUTE_TYPE;
typedef unsigned short ROUTE_NUM;
typedef unsigned int ROUTE_ID;
typedef unsigned long long CONNECT_KEY;

class RouteIdDefine
{
public:
	// src_route_id：路由ID开始端，dst_route_id：路由ID结束端
	inline static CONNECT_KEY CalcConnectKey(ROUTE_ID src_route_id, ROUTE_ID dst_route_id)
	{
		return (static_cast<CONNECT_KEY>(src_route_id) << (sizeof(ROUTE_ID) * 8)) | dst_route_id;
	}
	// route_id：路由ID
	inline static ROUTE_TYPE CalcRouteType(ROUTE_ID route_id)
	{
		return static_cast<ROUTE_TYPE>(route_id >> (sizeof(ROUTE_NUM) * 8));
	}
	// route_id：路由编号
	inline static ROUTE_NUM CalcRouteNum(ROUTE_ID route_id)
	{
		return static_cast<ROUTE_NUM>(route_id & static_cast<ROUTE_ID>(static_cast<ROUTE_NUM>(-1)));
	}
	// route_type：路由类型
	// route_num：路由编号
	inline static ROUTE_ID CalcRouteId(ROUTE_TYPE route_type, ROUTE_NUM route_num)
	{
		return (static_cast<ROUTE_ID>(route_type) << (sizeof(ROUTE_NUM) * 8)) | route_num;
	}

	// 计算路由信息
	inline static std::string CalcRouteName(ROUTE_ID route_id)
	{
		const ROUTE_TYPE route_type = CalcRouteType(route_id);
		const ROUTE_NUM route_num = CalcRouteNum(route_id);
		
		// 与RouteSystem.alittle的RouteType同步
		std::string route_name = std::to_string(route_type);
		switch (route_type)
		{
		case 1: route_name = "GATEWAY"; break;
		case 2: route_name = "DATA"; break;
		case 3: route_name = "VERSION"; break;
		case 4: route_name = "OPS"; break;
		case 5: route_name = "LOG"; break;
		case 6: route_name = "FILE"; break;
		case 7: route_name = "GAME"; break;
		case 8: route_name = "WEB"; break;
		case 9: route_name = "DEPLOY"; break;
		case 10: route_name = "MAP"; break;
		case 11: route_name = "SIP"; break;
		}
		return route_name + "_" + std::to_string(route_num);
	}

	// 计算连接信息
	inline static std::string CalcConnectName(CONNECT_KEY connect_key)
	{
		const ROUTE_ID src_route_id = connect_key >> (sizeof(ROUTE_ID) * 8);
		const ROUTE_ID dst_route_id = static_cast<ROUTE_ID>(connect_key & static_cast<CONNECT_KEY>(static_cast<ROUTE_ID>(-1)));
		return CalcRouteName(src_route_id) + "->" + CalcRouteName(dst_route_id);
	}

}; // RouteIdDefine

#define ROUTE2S(route_id) RouteIdDefine::CalcRouteName(route_id)
#define CONNECT2S(connect_key) RouteIdDefine::CalcConnectName(connect_key)

#endif // _ALITTLE_ROUTEIDDEFINE_H_
