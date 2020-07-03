
#ifndef _ALITTLE_ALITTLESCRIPTINDEX_H_
#define _ALITTLE_ALITTLESCRIPTINDEX_H_

#include <unordered_map>
#include <map>
#include <set>
#include <memory>
#include <vector>

class ABnfFile;
class ABnfElement;
class ABnfGuess;
struct ABnfGuessError;
class ALittleScriptClassData;
class ALittleScriptStructData;
class ALittleScriptEnumData;
class ALittleScriptAccessData;
class ALittleScriptNamespaceNameDecElement;
class ABnfProject;

struct RelayInfo
{
    std::set<RelayInfo*> be_used_set; // 被依赖集合
    std::set<RelayInfo*> use_set;    // 依赖集合

    std::string path;
    std::set<std::string> relay_set;
    std::string rel_path;
};

class ALittleScriptIndex
{
protected:
    // 保存关键的元素对象，用于快速语法树解析
    // Key1:文件对象，Key2:元素对象，Value:类型
    std::unordered_map<ABnfFile*, std::map<std::shared_ptr<ABnfElement>, std::vector<std::shared_ptr<ABnfGuess>>>> m_guess_type_map;
    std::unordered_map<ABnfFile*, std::map<std::shared_ptr<ABnfElement>, ABnfGuessError>> m_guess_error_map;
    // Key1:文件对象，Key2:名称，Value:数据
    std::unordered_map<ABnfFile*, std::unordered_map<std::string, ALittleScriptClassData*>> m_class_data_map;
    std::unordered_map<ABnfFile*, std::unordered_map<std::string, ALittleScriptStructData*>> m_struct_data_map;
    std::unordered_map<ABnfFile*, std::unordered_map<std::string, ALittleScriptEnumData*>> m_enum_data_map;

    // 按命名域来划分
    // string 表示命名域
    std::unordered_map<std::string, std::map<std::shared_ptr<ALittleScriptNamespaceNameDecElement>, ALittleScriptAccessData*>> m_all_data_map;
    // 根据开放权限来划分
    // string 表示命名域
    std::unordered_map<std::string, ALittleScriptAccessData*> m_global_access_map;
    std::unordered_map<std::string, ALittleScriptAccessData*> m_namespace_access_map;
    std::unordered_map<ABnfFile*, ALittleScriptAccessData*> m_file_access_map;

public:
    std::shared_ptr<ABnfGuess> sIntGuess;
    std::shared_ptr<ABnfGuess> sDoubleGuess;
    std::shared_ptr<ABnfGuess> sStringGuess;
    std::shared_ptr<ABnfGuess> sBoolGuess;
    std::shared_ptr<ABnfGuess> sLongGuess;
    std::shared_ptr<ABnfGuess> sAnyGuess;

    std::shared_ptr<ABnfGuess> sConstIntGuess;
    std::shared_ptr<ABnfGuess> sConstDoubleGuess;
    std::shared_ptr<ABnfGuess> sConstStringGuess;
    std::shared_ptr<ABnfGuess> sConstBoolGuess;
    std::shared_ptr<ABnfGuess> sConstLongGuess;
    std::shared_ptr<ABnfGuess> sConstAnyGuess;

    std::unordered_map<std::string, std::vector<std::shared_ptr<ABnfGuess>>> sPrimitiveGuessListMap;
    std::unordered_map<std::string, std::shared_ptr<ABnfGuess>> sPrimitiveGuessMap;

    std::vector<std::shared_ptr<ABnfGuess>> sConstNullGuess;

    // 控制语句
    std::set<std::string> sCtrlKeyWord;

    ALittleScriptIndex();

    // 获取类型列表
    const std::vector<std::shared_ptr<ABnfGuess>>* GetGuessTypeList(std::shared_ptr<ABnfElement> element);

    // 添加类型
    void AddGuessTypeList(std::shared_ptr<ABnfElement> element, const std::vector<std::shared_ptr<ABnfGuess>>& guess_type_list);

    // 获取类型错误
    ABnfGuessError* GetGuessError(std::shared_ptr<ABnfElement> element);

    // 添加类型错误
    void AddGuessError(std::shared_ptr<ABnfElement> element, const ABnfGuessError& error);

public:
    // 删除文件夹
    static bool GetDeepFilePaths(ABnfProject* project, const std::string& cur_path, const std::string& parent_path, std::vector<std::string>& result, ABnfGuessError& error)
    {
        if (project == nullptr) return false;
        if (!ALittleScriptUtility::IsDirExist(cur_path)) return false;

        // 初始化依赖信息
        std::unordered_map<std::string, RelayInfo> relay_map;
        var file_list = info.GetFiles();
        for (FileInfo file in file_list)
        {
            var full_path = file.DirectoryName + "\\" + file.Name;
            var relay_set = new HashSet<string>();
            FindDefineRelay(project, full_path, relay_set);
            var relay_info = new RelayInfo();
            relay_info.path = full_path;
            relay_info.rel_path = parent_path + file.Name;
            relay_info.relay_set = relay_set;
            relay_info.be_used_set = new HashSet<RelayInfo>();
            relay_info.use_set = new HashSet<RelayInfo>();
            if (relay_map.ContainsKey(relay_info.path)) relay_map.Remove(relay_info.path);
            relay_map.Add(relay_info.path, relay_info);
        }

        // 形成通路
        foreach(var relay_info in relay_map.Values)
        {
            foreach(string child_path in relay_info.relay_set)
            {
                relay_map.TryGetValue(child_path, out var child);
                if (child == null) continue;
                if (!child.be_used_set.Contains(relay_info))
                    child.be_used_set.Add(relay_info);
                if (!relay_info.use_set.Contains(child))
                    relay_info.use_set.Add(child);
            }
        }

        // 都放进列表中，并排序
        var info_list = new List<RelayInfo>();
        info_list.AddRange(relay_map.Values);
        info_list.Sort((RelayInfo a, RelayInfo b) = > { return a.path.CompareTo(b.path); });

        // 遍历列表
        while (info_list.Count > 0)
        {
            // 用于接收未处理的列表
            var new_info_list = new List<RelayInfo>();
            // 遍历列表进行处理
            foreach(var relay_info in info_list)
            {
                // 如果已经没有依赖了，那么就添加进result，然后解除依赖关系
                if (relay_info.use_set.Count == 0)
                {
                    result.Add(relay_info.rel_path);
                    foreach(var be_used_info in relay_info.be_used_set)
                        be_used_info.use_set.Remove(relay_info);
                    relay_info.be_used_set.Clear();
                }
                else {
                    new_info_list.Add(relay_info);
                }
            }
            // 如果一轮下来没有减少，那么就抛异常
            if (new_info_list.Count == info_list.Count)
            {
                string content = "";
                foreach(var relayInfo in new_info_list)
                {
                    content += relayInfo.rel_path + " -> ";
                    foreach(var use_info in relayInfo.use_set)
                        content += use_info.rel_path;
                    content += ";";
                }
                return new ABnfGuessError(null, "出现循环引用 " + content);
            }

            // 把收集的列表复制给info_list，进行下一轮循环
            info_list = new_info_list;
        }

        var dir_list = info.GetDirectories();
        foreach(DirectoryInfo file in dir_list)
        {
            var error = GetDeepFilePaths(project, file, parent_path + file.Name + "/", result);
            if (error != null) return error;
        }

        return null;
    }
    
    static ABnfGuessError FindDefineRelay(ProjectInfo project, string file_path, HashSet<string> result)
    {
        var file = project.GetFile(file_path);
        if (file == null) return null;

        var abnf_file = file.GetFile();
        if (abnf_file == null) return null;

        var dec = ALittleScriptUtility.GetNamespaceDec(abnf_file);
        if (dec == null) return null;
        var element_dec_list = dec.GetNamespaceElementDecList();
        foreach(var element_dec in element_dec_list)
        {
            if (element_dec.GetClassDec() != null)
            {
                var extendsDec = element_dec.GetClassDec().GetClassExtendsDec();
                if (extendsDec == null) continue;
                var error = extendsDec.GuessType(out var guess);
                if (!(guess is ALittleScriptGuessClass)) continue;
                var element = ((ALittleScriptGuessClass)guess).GetElement();
                if (element == null) continue;
                if (file_path == element.GetFullPath()) continue;
                result.Add(element.GetFullPath());
            }
        }
        return null;
    }

};

#endif // _ALITTLE_ALITTLESCRIPTINDEX_H_
