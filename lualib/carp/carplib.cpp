
extern "C" {
#include "carplib.h"
}

#include "carp_net_bind.hpp"
#include "carp_message_bind.hpp"
#include "carp_crypto_bind.hpp"
#include "carp_log_bind.hpp"
#include "carp_csv_bind.hpp"
#include "carp_timer_bind.hpp"
#include "carp_file_bind.hpp"
#include "carp_string_bind.hpp"
#include "carp_bit_bind.hpp"
#include "carp_rwops_bind.hpp"
#include "carp_task_consumer_bind.hpp"

#define CARP_CONSOLE_IMPL
#include "carp_console.hpp"
#define CARP_DUMP_IMPL
#include "carp_dump.hpp"

#define CARP_LOG_IMPL
#include "carp_log.hpp"

#define CARP_RWOPS_IMPL
#include "carp_rwops.h"

#define CARP_TASK_CONSUMER_IMPL
#include "carp_task_consumer.hpp"

int luaopen_carp(lua_State* l_state) {
	CarpMessageBind::Bind(l_state);
	CarpCryptoBind::Bind(l_state);
	CarpLogBind::Bind(l_state);
	CarpCsvBind::Bind(l_state);
	CarpTimerBind::Bind(l_state);
	CarpFileBind::Bind(l_state);
	CarpStringBind::Bind(l_state);
	CarpBitBind::Bind(l_state);
	CarpRWopsBind::Bind(l_state);
	CarpTaskConsumerBind::Bind(l_state);
	CarpNetBind::Bind(l_state);
    lua_getglobal(l_state, "carp");
    return 1;
}
