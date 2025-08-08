add_rules("mode.debug", "mode.release")


for _, file in ipairs(os.files("src/*.cpp")) do
    local filename = path.basename(file)
    -- Extract short name (e.g., "1_1" from "1_1-simple_factory.cpp", or 1 from "1-another_example.cpp")
    local short_name = filename:match("^(%d+_+%d+)-") or filename:match("^(%d+)-")
    if short_name then
        -- print("Adding target: " .. short_name .. " -> " .. filename)
        target(short_name)
        do
            set_kind("binary")
            add_files(file)
            target_end()
        end
    else
        -- print("Filename does not match expected pattern: " .. filename)
        target(filename)
        do
            set_kind("binary")
            add_files(file)
            target_end()
        end
    end
end
