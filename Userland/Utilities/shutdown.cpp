/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Liav A. <liavalb@hotmail.co.il>
 * Copyright (c) 2022, Alex Major
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/ByteString.h>
#include <LibCore/File.h>
#include <LibMain/Main.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

ErrorOr<int> serenity_main(Main::Arguments)
{
    auto file = TRY(Core::File::open("/sys/kernel/power_state"sv, Core::File::OpenMode::Write));

    ByteString const file_contents = "2";
    TRY(file->write_until_depleted(file_contents.bytes()));
    file->close();

    return 0;
}
