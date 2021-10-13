
#ifndef _ALITTLE_ALITTLESCRIPTUTILITY_H_
#define _ALITTLE_ALITTLESCRIPTUTILITY_H_

#include <string>
#include <memory>
#include <vector>

#include "ALittleScriptDefine.h"

class ALittleScriptNumberElement;
class ALittleScriptGuessStruct;
class ALittleScriptModifierElement;
class ABnfElement;
struct ABnfGuessError;
class ABnfFile;
class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;
class ALittleScriptNamespaceDecElement;
class ALittleScriptNamespaceNameDecElement;
class ALittleScriptClassDecElement;
class ALittleScriptTemplateDecElement;
class ALittleScriptStructDecElement;
class ALittleScriptStructVarDecElement;
class ALittleScriptEnumDecElement;
class ALittleScriptEnumVarDecElement;
class ALittleScriptVarAssignNameDecElement;
class ALittleScriptClassCtorDecElement;
class ALittleScriptMethodParamNameDecElement;
class ALittleScriptForExprElement;
class ALittleScriptForConditionElement;
class ALittleScriptAllExprElement;
class ALittleScriptValueStatElement;

class ALittleScriptUtility
{
public:
    // ɾ����ߵĿո�
    static void TrimLeft(std::string& target);

    // ɾ���ұߵĿո�
    static void TrimRight(std::string& target);

	// �����ļ���
	static void CreateFolder(const std::string& path);

	// �ݹ鴴���ļ���
	static void CreateDeepFolder(const std::string& path);

    // �ж��ļ��Ƿ����
    static bool IsFileExist(const std::string& path);

    // �ж��ļ��Ƿ����
    static bool IsDirExist(const std::string& path);

    // ��ȡ�ļ����µ������ļ�
    static void GetNameListInFolder(const std::string& path, std::vector<std::string>& file_list, std::vector<std::string>& dir_list);

    // �ı���չ��
    static std::string ChangeFileExtByPath(const std::string& file_path, const std::string& ext);

    // ��·���л�ȡ�ļ���
    static std::string GetFilePathByPath(const std::string& file_path);

    // �ж��ַ����ǲ�������ֵ
	static bool IsInt(const std::shared_ptr<ALittleScriptNumberElement>& element);

    // �����ϣֵ
	static int JSHash(const std::string& content);

	// ����ṹ��Ĺ�ϣֵ
	static int StructHash(const std::shared_ptr<ALittleScriptGuessStruct>& guess);

    // �����ж�
    static bool IsLanguageEnable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // �Ƿ�ʹ��ԭ��
    static bool IsNative(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ���await
    static ABnfGuessError CheckInvokeAwait(std::shared_ptr<ABnfElement> element);

    // �ж��Ƿ����
    static ABnfGuessError CheckError(const std::shared_ptr<ABnfElement>& parent, const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ��ȡ�Ƿ���register
    static bool IsRegister(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ��ȡ�Ƿ���Const
    static bool IsConst(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ��ȡ�Ƿ���Nullable
    static bool IsNullable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ��ȡЭ������
    static std::string GetCoroutineType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ��ȡЭ������
    static std::string GetProtocolType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ��ȡ��������
    static bool GetCommandDetail(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& cmd, std::string& desc);

    // ��ȡ����Ȩ������
    static ClassAccessType CalcAccessType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // ����Ȩ�޵ȼ�
    static const int sAccessOnlyPublic = 1;                    // ���Է���public�����Ժͷ���
    static const int sAccessProtectedAndPublic = 2;            // ���Է���public protected�����Ժͷ���
    static const int sAccessPrivateAndProtectedAndPublic = 3;  // ����public protected private�����Ժͷ���

    // ��ȡĳ��Ԫ�ص����������
    static std::shared_ptr<ALittleScriptNamespaceDecElement> GetNamespaceDec(ABnfFile* file);

    // ��ȡĳ��Ԫ�ص�������������
    static std::shared_ptr<ALittleScriptNamespaceNameDecElement> GetNamespaceNameDec(ABnfFile* file);

    // �ж�ĳ���ǲ���register
    static bool IsRegister(const std::shared_ptr<ABnfElement>& element);
    static bool IsRegister(ABnfFile* file);

    // ��ȡĳ��Ԫ�ص���������
    static const std::string& GetNamespaceName(const std::shared_ptr<ABnfElement>& element);

    // ��ȡ��������
    static const std::string& GetNamespaceName(ABnfFile* file);

    // ��ȡ���Ԫ�����ڵ���
    static std::shared_ptr<ALittleScriptClassDecElement> FindClassDecFromParent(std::shared_ptr<ABnfElement> dec);

    // ��ȡ���Ԫ�����ڵĺ���ģ��
    static std::shared_ptr<ALittleScriptTemplateDecElement> FindMethodTemplateDecFromParent(std::shared_ptr<ABnfElement> dec);

    // ����Ƿ��ھ�̬������
    static bool IsInClassStaticMethod(const std::shared_ptr<ABnfElement>& dec);

    // �������ƣ���ȡ����ṹ��ĳ�Ա�б�
    static void FindStructVarDecList(const std::shared_ptr<ALittleScriptStructDecElement>& dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& result, int deep);

    // �������ƣ���ȡ���ö���еĳ�Ա
    static void FindEnumVarDecList(const std::shared_ptr<ALittleScriptEnumDecElement>& dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& result);

    // ����struct�ĸ���
    static std::shared_ptr<ALittleScriptStructDecElement> FindStructExtends(const std::shared_ptr<ALittleScriptStructDecElement>
	    & dec);

    // ����class�ĸ���
    static std::shared_ptr<ALittleScriptClassDecElement> FindClassExtends(const std::shared_ptr<ALittleScriptClassDecElement>
	    & dec);

    // ����������ͬ��Ԫ��
    static void FilterSameName(const std::vector<std::shared_ptr<ABnfElement>>& list, std::vector<std::shared_ptr<ABnfElement>>& out);


    // ������dec������У���targetDec��Ա�ķ���Ȩ��
    static int CalcAccessLevelByTargetClassDec(int access_level, const std::shared_ptr<ALittleScriptClassDecElement>&
                                               dec, const std::shared_ptr<ALittleScriptClassDecElement>& target_dec);

    // ��������Ԫ�ط���targetDec�ķ���Ȩ��
    static int CalcAccessLevelByTargetClassDecForElement(const std::shared_ptr<ABnfElement>& element, const std::shared_ptr<ALittleScriptClassDecElement>
                                                         & target_dec);

    // �������ƣ���ȡ�����б�
    static void FindClassMethodNameDecList(const std::shared_ptr<ALittleScriptClassDecElement>& dec, int access_level, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result, int deep);

    // �������ƣ���ȡ��������б�
    static void FindClassAttrList(const std::shared_ptr<ALittleScriptClassDecElement>& dec
                                  , int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result, int deep);

    // �������ƣ���ȡ�̳еĹ��캯��
    static std::shared_ptr<ALittleScriptClassCtorDecElement> FindFirstCtorDecFromExtends(const std::shared_ptr<ALittleScriptClassDecElement>
                                                                                         & dec, int deep);

    // �������ƣ���ȡ�̳е�����
    static std::shared_ptr<ABnfElement> FindFirstClassAttrFromExtends(const std::shared_ptr<ALittleScriptClassDecElement>
                                                                      & dec, ClassAttrType attr_type, const std::string& name, int deep);

    // �������ƣ����Һ����Ĳ����б�
    static void FindMethodParamNameDecList(const std::shared_ptr<ABnfElement>& method_dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>>& result);

    // �������ƣ����ұ��������ڵĶ���Ԫ��
    static void FindVarAssignNameDecList(const std::shared_ptr<ABnfElement>& element, const std::string& name, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result);

    static void FindVarAssignNameDecList(const std::shared_ptr<ALittleScriptForExprElement>& for_expr, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name);
    
    static void FindVarAssignNameDecList(const std::shared_ptr<ALittleScriptForConditionElement>& for_condition, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name);

    // �������ƣ����Ҷ�����ʽ���б�
    static void FindVarAssignNameDecList(const std::shared_ptr<ALittleScriptAllExprElement>& all_expr, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name);

    // ����������
    static bool IsPairsFunction(const std::vector<ABnfGuessPtr>& guess_list);

    // ������ʽ��Ҫʹ��ʲô���ı�����ʽ
    static ABnfGuessError CalcPairsTypeForLua(const std::shared_ptr<ALittleScriptValueStatElement>& value_stat, std::string& result);

    // ������ʽ��for��ʹ��in����of
    static ABnfGuessError CalcPairsTypeForJavaScript(const std::shared_ptr<ALittleScriptValueStatElement>& value_stat, std::string& result, bool& is_native);

    // �ж� parent�Ƿ���child�ĸ���
    static ABnfGuessError IsClassSuper(const std::shared_ptr<ALittleScriptClassDecElement>& child, const std::string& parent, bool& result);

    // �ж� parent�Ƿ���child�ĸ���
    static ABnfGuessError IsStructSuper(const std::shared_ptr<ABnfElement>& child, const std::string& parent, bool& result);

    // ��ȡĿ���·��
    static std::string CalcRootFullPath(const std::string& project_path, const std::string& ext);

    // ��ȡĿ���ļ�·��
    static std::string CalcTargetFullPath(const std::string& project_path, const std::string& ali_full_path, const std::string& ext, std::string& error);

    // �ж�ValueStat
    static ABnfGuessError CalcReturnCount(const std::shared_ptr<ALittleScriptValueStatElement>& value_stat, int& count, std::vector<ABnfGuessPtr>& guess_list);
};

#endif // _ALITTLE_ALITTLESCRIPTUTILITY_H_
