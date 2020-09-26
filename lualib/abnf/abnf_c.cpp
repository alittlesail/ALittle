
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "abnf_c.h"
}

#include "Index/ABnfProjectClass.h"
#include "Index/ABnfFileClass.h"

void* create_abnf_project(const char* abnf_buffer)
{
	auto* project = new ABnfProjectClass();
	project->Start(abnf_buffer);
	return project;
}

void delete_abnf_project(void* project)
{
	delete ((ABnfProjectClass*)project);
}

void* create_abnf_file(void* project, const char* full_path, const char* text, size_t len)
{
	return new ABnfFileClass((ABnfProject*)project, full_path, text, len, true);
}

void delete_abnf_file(void* file)
{
	delete ((ABnfFileClass*)file);
}

void abnffile_generate(void* file, int query_id, int version, const char* target_path, const char* language_name)
{
	auto* project_c = (ABnfProjectClass*)(((ABnfFileClass*)file)->GetProject());
	project_c->Add(std::bind(&ABnfProjectClass::Generate, project_c, ((ABnfFileClass*)file)->GetFullPath(), query_id, version, std::string(target_path), std::string(language_name)));
}
