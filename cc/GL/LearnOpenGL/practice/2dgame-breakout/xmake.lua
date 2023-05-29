add_rules("mode.debug", "mode.release")

add_requires("glfw","glad","glm","stb")


set_targetdir("bin")

target("breakout")
    set_kind("binary")
    add_files("src/*.cpp")
	add_packages("glfw","glad","glm","stb")

