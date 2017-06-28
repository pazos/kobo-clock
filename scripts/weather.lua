-- Fetch weather forecast from openweathermap.org.

http = require("socket.http")
json = require("json")

url_template = "http://api.openweathermap.org/data/2.5/weather?id="
app_id = "fc8dee36012891cd0cf2fc371eff2a32" -- API_KEY
city_id = "3105575"

weather = http.request(url_template..city_id.."&units=metric&appid="..app_id)
if weather == nil then
    log = io.open("/tmp/system.log", "a")
    io.output(log)
    io.write("[weather.lua]: Unable to fetch the weather data\n")
    io.close(log)
    os.exit()
end

response = json.decode(weather)
math.round = function (n)
    return math.floor(n + 0.5)
end

temp = response.main.temp
icon = response.weather[1].icon
city = response.name

data_storage = "/opt/kobo-clock/data/weather.forecast"

log = io.open("/tmp/system.log", "a")
io.output(log)
io.write("[weather.lua]: fetching data:\n City: ", city, "\n Temperature: ",
         temp, "\n Icon: ", icon, ".bmp\n")
io.close(log)

file = io.open(data_storage, "w")
io.output(file)
io.write(city, "|", math.round(temp), "|", icon, ".bmp")
io.close(file)
