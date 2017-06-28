-- check battery status
local syspath = "/sys/devices/platform/pmic_battery.1/power_supply/mc13892_bat/"
local capacity= io.open(syspath .. "capacity", "r")
local status = io.open(syspath .. "status", "r")

-- read the capacity:
io.input(capacity)
percent=io.read()
io.close(capacity)

-- read the status:
io.input(status)
charging=io.read()
io.close(status)

if charging ~= nil then
    io.write(percent, "% ", charging, "\n")
else
    io.write(percent, "%\n")
end
