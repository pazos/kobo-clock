-- handle kobo buttons (values for Kobo Aura HD)
local evdev = require "evdev"
local kobo_pad = evdev.Device "/dev/input/event0"

while true do
    local timestamp, eventType, eventCode, value = kobo_pad:read()
    if eventType == evdev.EV_KEY and eventCode == 90 and value == 0 then
        -- repurpose frontlight button to -- snooze --
        os.execute("/opt/kobo-clock/bin/snooze")
    end
    if eventType == evdev.EV_KEY and eventCode == 116 and value == 0 then
        -- use the power button to turn off the device. Display image first
        os.execute("zcat /opt/kobo-clock/data/off.raw.gz | pickel showpic 0")
        os.execute("/sbin/poweroff")
    end
end
