#define LOG_TAG "HelloWorldService"

#include <utils/Log.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include <string.h>
#include <cutils/atomic.h>
#include <utils/Errors.h>
#include <binder/IServiceManager.h>
#include <utils/String16.h>

#include "helloworldservice.h"
#include "utils/Log.h"

#include <unistd.h>

const android::String16 IHelloWorldService::descriptor(HELLOWORLD_NAME);

android::String16 IHelloWorldService::getInterfaceDescriptor() {
        return IHelloWorldService::descriptor;
}


void HelloWorldService::instantiate() {
	android::defaultServiceManager()->addService(
                IHelloWorldService::descriptor, new HelloWorldService());
}

HelloWorldService::HelloWorldService()
{
    ALOGE("HelloWorldService created");
    mNextConnId = 1;
}

HelloWorldService::~HelloWorldService()
{
    ALOGE("HelloWorldService destroyed");
}

#define CHECK_INTERFACE(interface, data, reply) \
        do { if (!data.enforceInterface(interface::getInterfaceDescriptor())) { \
            ALOGW("Call incorrectly routed to " #interface); \
            return android::PERMISSION_DENIED;              \
        } } while (0)

android::status_t HelloWorldService::onTransact(uint32_t code,
                                                const android::Parcel &data,
                                                android::Parcel *reply,
                                                uint32_t flags)
{
        ALOGE("OnTransact(%u,%u)", code, flags);
        
        switch(code) {
        case HW_HELLOTHERE: {
                CHECK_INTERFACE(IHelloWorldService, data, reply);
                const char *str;
                str = data.readCString();
                /* hellothere(str); */
                ALOGE("hello: %s\n", str);
                printf("hello: %s\n", str);
                return android::NO_ERROR;
        } break;
        default:
                return BBinder::onTransact(code, data, reply, flags);
        }

        return android::NO_ERROR;
}

