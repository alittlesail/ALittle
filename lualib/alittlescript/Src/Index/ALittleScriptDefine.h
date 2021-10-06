
#ifndef _ALITTLE_ALITTLESCRIPTDEFINE_H_
#define _ALITTLE_ALITTLESCRIPTDEFINE_H_

// �����������
enum class ClassAttrType
{
    VAR,            // ��Ա����
    FUN,            // ��Ա����
    GETTER,         // getter����
    SETTER,         // setter����
    STATIC,         // ��̬����
    TEMPLATE,       // ģ�����
};

// ����Ȩ������
enum class ClassAccessType
{
    PUBLIC,         // ȫ�ֿɷ���
    PROTECTED,      // ��������ɷ���
    PRIVATE,        // ����ɷ���
};

// Ԫ������
enum class ABnfElementType
{
    CLASS_NAME,         // ����
    ENUM_NAME,          // ö����
    STRUCT_NAME,        // �ṹ����
    INSTANCE_NAME,      // ������
    GLOBAL_METHOD,      // ȫ�ֺ���
    USING_NAME,         // using��
};

#endif // _ALITTLE_ALITTLESCRIPTDEFINE_H_
