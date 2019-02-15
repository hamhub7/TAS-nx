/*
 * Copyright (c) 2018 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <mutex>
#include <switch.h>
#include "hid_mitm_service.hpp"
#include "hid_mitm_iappletresource.hpp"
#include "hid_custom.h"

void HidMitmService::PostProcess(IMitmServiceObject *obj, IpcResponseContext *ctx) {
    /* No commands need postprocessing. */    
}

Result HidMitmService::CreateAppletResource(Out<std::shared_ptr<IAppletResourceMitmService>> out,PidDescriptor pid, u64 aruid)
{
    customHidInitialize(this->forward_service.get());


    std::shared_ptr<IAppletResourceMitmService> intf = nullptr;



    intf = std::make_shared<IAppletResourceMitmService>(new IAppletResourceMitmService(0));
    //intf->hid_service = this->forward_service.get();

    out.SetValue(std::move(intf));
    if (out.IsDomain()) {
        fatalSimple(0x111); // Doesn't seem to ever happen thankfully
    }
    return 0;
}

Result HidMitmService::ReloadConfig() {
    loadConfig();
    return 0;
}
