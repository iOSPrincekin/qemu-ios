#include "hw/arm/ipod_touch_sysic.h"

static uint64_t ipod_touch_sysic_read(void *opaque, hwaddr addr, unsigned size)
{
    IPodTouchSYSICState *s = (IPodTouchSYSICState *) opaque;

    //fprintf(stderr, "%s: offset = 0x%08x\n", __func__, addr);

    switch (addr) {
        case POWER_ID:
            //return (3 << 24); //for older iboots
            return (2 << 0x18);
        case 0x7a:
        case 0x7c:
            return 1;
        case POWER_SETSTATE:
        case POWER_STATE:
            return s->power_state;
      default:
        break;
    }
    return 0;
}

static void ipod_touch_sysic_write(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    IPodTouchSYSICState *s = (IPodTouchSYSICState *) opaque;

    //fprintf(stderr, "%s: writing 0x%08x to 0x%08x\n", __func__, val, addr);

    switch (addr) {
        case POWER_ONCTRL:
            if((val & 0x20) != 0 || (val & 0x4) != 0 || (val & POWER_ID_ADM) != 0) { break; } // make sure that we do not record the 'on' state of some devices so it appears like they are turned on immediately.
            s->power_state = val;
            break;
        case POWER_OFFCTRL:
            s->power_state = val;
            break;
        default:
            break;
    }
}

static const MemoryRegionOps ipod_touch_sysic_ops = {
    .read = ipod_touch_sysic_read,
    .write = ipod_touch_sysic_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void ipod_touch_sysic_init(Object *obj)
{
    DeviceState *dev = DEVICE(obj);
    IPodTouchSYSICState *s = IPOD_TOUCH_SYSIC(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

    memory_region_init_io(&s->iomem, obj, &ipod_touch_sysic_ops, s, TYPE_IPOD_TOUCH_SYSIC, 0x1000);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);
}

static void ipod_touch_sysic_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
}

static const TypeInfo ipod_touch_sysic_type_info = {
    .name = TYPE_IPOD_TOUCH_SYSIC,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(IPodTouchSYSICState),
    .instance_init = ipod_touch_sysic_init,
    .class_init = ipod_touch_sysic_class_init,
};

static void ipod_touch_sysic_register_types(void)
{
    type_register_static(&ipod_touch_sysic_type_info);
}

type_init(ipod_touch_sysic_register_types)
