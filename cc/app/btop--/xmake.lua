add_rules("mode.debug", "mode.release")

set_languages("c++20")

target("btop--")
    set_kind("binary")
    add_files("src/*.cpp")

