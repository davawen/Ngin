#include "ngin.h"

static void default_framebuffer_resize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ngin_end_frame(GLFWwindow *window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

GLFWwindow *ngin_init(i32 window_width, i32 window_height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "OpenGL", NULL, NULL);
	if (window == NULL) {
		LOG("error: failed to created glfw window\n");
		return NULL;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		LOG("error: failed to load GLEW\n");
		return NULL;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	LOG("info: renderer: %s\n", renderer);
	LOG("info: OpenGL version supported %s\n", version);

	glViewport(0, 0, window_width, window_height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSetFramebufferSizeCallback(window, default_framebuffer_resize);

	return window;
}

void ngin_destroy(void) {
	glfwTerminate();
}
