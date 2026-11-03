/**
 * RDP-client: Modern X11 RDP Client
 * X11 Command Line
 *
 * Copyright 2026 William Poetra Yoga <william.poetra@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <freerdp/config.h>
#include <freerdp/client/cmdline.h>

#include <stdlib.h>

#include "xf_cmdline.h"
#include "xfreerdp.h"

static const COMMAND_LINE_ARGUMENT_A xf_args[] = {
	{ "defer-alt", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr,
	  "Откладывать нажатие Alt до нажатия другой клавиши. При включении Alt-Tab не активирует "
	  "меню удалённого приложения. Полезно вместе с -grab-keyboard (по умолч.: off)" },
	{ "keepalive", COMMAND_LINE_VALUE_BOOL | COMMAND_LINE_VALUE_OPTIONAL, "<секунды, по умолч. 300>",
	  nullptr, nullptr, -1, nullptr,
	  "Имитировать активность пользователя (смещение мыши ±1 px + Shift) каждые N секунд, "
	  "чтобы удалённая сессия не блокировалась по таймауту (по умолч.: off)" },
	{ nullptr, 0, nullptr, nullptr, nullptr, -1, nullptr, nullptr }
};

static int xf_client_handle_option(const COMMAND_LINE_ARGUMENT_A* arg, void* custom)
{
	xfContext* xfc = custom;
	WINPR_ASSERT(xfc);
	WINPR_ASSERT(arg);

	if (arg->Name && (strcmp(arg->Name, "defer-alt") == 0))
	{
		xfc->deferAlt = arg->Value != nullptr;
		return 0;
	}
	if (arg->Name && (strcmp(arg->Name, "keepalive") == 0))
	{
		if (arg->Value == BoolValueFalse)
		{
			xfc->keepalive = FALSE;
		}
		else if (arg->Value && (arg->Value != BoolValueTrue))
		{
			const int seconds = atoi(arg->Value);
			if (seconds < 5)
				xfc->keepalive_interval = 5;
			else if (seconds > 86400)
				xfc->keepalive_interval = 86400; /* 1 day max */
			else
				xfc->keepalive_interval = (UINT32)seconds;
			xfc->keepalive = TRUE;
		}
		else
		{
			xfc->keepalive_interval = 300; /* 5 minutes */
			xfc->keepalive = TRUE;
		}
		return 0;
	}
	return 0;
}

int xf_client_settings_parse_command_line(xfContext* xfc, int argc, char** argv)
{
	WINPR_ASSERT(xfc);

	COMMAND_LINE_ARGUMENT_A args[ARRAYSIZE(xf_args)] = WINPR_C_ARRAY_INIT;
	memcpy(args, xf_args, sizeof(args));

	xfc->deferAlt = FALSE;
	xfc->keepalive = FALSE;
	xfc->keepalive_interval = 300;
	return freerdp_client_settings_parse_command_line_ex(xfc->common.context.settings, argc, argv,
	                                                     FALSE, args, ARRAYSIZE(args) - 1,
	                                                     xf_client_handle_option, xfc);
}

int xf_client_settings_command_line_status_print(xfContext* xfc, int status, int argc, char** argv)
{
	WINPR_ASSERT(xfc);
	return freerdp_client_settings_command_line_status_print_ex(xfc->common.context.settings,
	                                                            status, argc, argv, xf_args);
}
