
#ifndef _ALITTLE_ABNFPROJECT_H_
#define _ALITTLE_ABNFPROJECT_H_

#include <string>
#include <vector>

class ABnfProject
{
private:
	std::string m_project_path;

public:
	const std::string& GetProjectPath() const { return m_project_path; }
};

#endif // _ALITTLE_ABNFPROJECT_H_