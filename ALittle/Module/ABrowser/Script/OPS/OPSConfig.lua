
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-80894039, "ABrowser.OPSDialogFieldConfig", {
name = "ABrowser.OPSDialogFieldConfig", ns_name = "ABrowser", rl_name = "OPSDialogFieldConfig", hash_code = -80894039,
name_list = {"x","y","width","height","name","invoke_param","input_param","input_type","__select_dialog","show_field","select_field","show_param","data_list","data_map","default_value","unit","select_type","default_hour","default_min","default_sec"},
type_list = {"double","double","double","double","string","string","string","string","string","string","string","string","List<string>","Map<string,any>","string","string","string","int","int","int"},
option_map = {}
})
ALittle.RegStruct(1434775091, "ABrowser.OPSSendParamConfig", {
name = "ABrowser.OPSSendParamConfig", ns_name = "ABrowser", rl_name = "OPSSendParamConfig", hash_code = 1434775091,
name_list = {"key","type"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-2053533300, "ABrowser.OPSDialogConfig", {
name = "ABrowser.OPSDialogConfig", ns_name = "ABrowser", rl_name = "OPSDialogConfig", hash_code = -2053533300,
name_list = {"__class","title","content","permission","send_param","field","__table_data","module_invoke"},
type_list = {"string","string","string","string","Map<string,ABrowser.OPSSendParamConfig>","List<ABrowser.OPSDialogFieldConfig>","string","bool"},
option_map = {}
})
ALittle.RegStruct(-1488923450, "ABrowser.OPSTableQueryConfig", {
name = "ABrowser.OPSTableQueryConfig", ns_name = "ABrowser", rl_name = "OPSTableQueryConfig", hash_code = -1488923450,
name_list = {"name","input_type","query_param","field_param","operation","value_type","width","option","data_list","data_map","default_value","select_day","default_hour","default_min","default_sec"},
type_list = {"string","string","string","string","string","string","double","bool","List<string>","Map<string,any>","string","bool","int","int","int"},
option_map = {}
})
ALittle.RegStruct(1107102769, "ABrowser.OPSTableDataStyleConfig", {
name = "ABrowser.OPSTableDataStyleConfig", ns_name = "ABrowser", rl_name = "OPSTableDataStyleConfig", hash_code = 1107102769,
name_list = {"time_format","enum_map","expand"},
type_list = {"string","Map<string,any>","double"},
option_map = {}
})
ALittle.RegStruct(-1365386282, "ABrowser.OPSTableTdConfig", {
name = "ABrowser.OPSTableTdConfig", ns_name = "ABrowser", rl_name = "OPSTableTdConfig", hash_code = -1365386282,
name_list = {"width","name","hidden","order","data_handle","data_style","field","cross_db","cross_table","cross_field","cross_key","cross_src","cross_type","cross_operation"},
type_list = {"double","string","bool","bool","bool","ABrowser.OPSTableDataStyleConfig","string","string","string","string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(1111415205, "ABrowser.OPSTableConfig", {
name = "ABrowser.OPSTableConfig", ns_name = "ABrowser", rl_name = "OPSTableConfig", hash_code = 1111415205,
name_list = {"__class","db_name","table_name","permission","data_handle","query_info","table_td","tr_height"},
type_list = {"string","string","string","string","string","List<ABrowser.OPSTableQueryConfig>","List<ABrowser.OPSTableTdConfig>","double"},
option_map = {}
})
ALittle.RegStruct(1407431748, "ABrowser.OPSMainMenuConfig", {
name = "ABrowser.OPSMainMenuConfig", ns_name = "ABrowser", rl_name = "OPSMainMenuConfig", hash_code = 1407431748,
name_list = {"name","childs"},
type_list = {"string","List<ABrowser.OPSSubMenuConfig>"},
option_map = {}
})
ALittle.RegStruct(663353817, "ABrowser.OPSSubMenuConfig", {
name = "ABrowser.OPSSubMenuConfig", ns_name = "ABrowser", rl_name = "OPSSubMenuConfig", hash_code = 663353817,
name_list = {"name","table","single_handle","multi_handle","order"},
type_list = {"string","string","List<ABrowser.OPSHandleConfig>","List<ABrowser.OPSMultiHandleListInfo>","ABrowser.OPSSubMenuDefaultOrderConfig"},
option_map = {}
})
ALittle.RegStruct(-153240477, "ABrowser.OPSHandleConfig", {
name = "ABrowser.OPSHandleConfig", ns_name = "ABrowser", rl_name = "OPSHandleConfig", hash_code = -153240477,
name_list = {"name","dialog"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(1939442984, "ABrowser.OPSMultiHandleListInfo", {
name = "ABrowser.OPSMultiHandleListInfo", ns_name = "ABrowser", rl_name = "OPSMultiHandleListInfo", hash_code = 1939442984,
name_list = {"name","childs"},
type_list = {"string","List<ABrowser.OPSHandleConfig>"},
option_map = {}
})
ALittle.RegStruct(-2070150967, "ABrowser.OPSSubMenuDefaultOrderConfig", {
name = "ABrowser.OPSSubMenuDefaultOrderConfig", ns_name = "ABrowser", rl_name = "OPSSubMenuDefaultOrderConfig", hash_code = -2070150967,
name_list = {"name","type"},
type_list = {"string","bool"},
option_map = {}
})
ALittle.RegStruct(1409888415, "ABrowser.OPSBaseConfig", {
name = "ABrowser.OPSBaseConfig", ns_name = "ABrowser", rl_name = "OPSBaseConfig", hash_code = 1409888415,
name_list = {"ops_name","login_ip","login_port","icon_path","icon_width","icon_height"},
type_list = {"string","string","int","string","double","double"},
option_map = {}
})
ALittle.RegStruct(771043568, "ABrowser.OPSConfig", {
name = "ABrowser.OPSConfig", ns_name = "ABrowser", rl_name = "OPSConfig", hash_code = 771043568,
name_list = {"base","menu","table","dialog"},
type_list = {"ABrowser.OPSBaseConfig","List<ABrowser.OPSMainMenuConfig>","Map<string,ABrowser.OPSTableConfig>","Map<string,ABrowser.OPSDialogConfig>"},
option_map = {}
})

