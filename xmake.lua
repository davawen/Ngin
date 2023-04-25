add_requires("opengl", "glew", "glfw", "stb", "vcpkg::cglm")

target("engine")
	set_kind("shared")
	add_includedirs("include", { public = true })
	add_headerfiles("include/*.h")
	add_files("engine/*.c")
	add_packages("opengl", "glew", "glfw", "stb", "vcpkg::cglm")

target("main")
	set_kind("binary")
	add_files("src/*.c")
	add_deps("engine")
	add_packages("opengl", "glew", "glfw", "vcpkg::cglm")
