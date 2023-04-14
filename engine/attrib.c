#include "log.h"
#include "attrib.h"

const BufferSchema simple_vertex_schema = {
	.num = 1,
	.attributes = (Attribute[]){
		{ GL_FLOAT, 3 }
	}
};

/// Takes a symbolic type constant and returns its size
static u64 sizeof_gltype(GLenum type) {
	switch(type) {
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
			return sizeof(GLbyte);
		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
			return sizeof(GLshort);
		case GL_INT_2_10_10_10_REV:
		case GL_INT:
		case GL_UNSIGNED_INT_2_10_10_10_REV:
		case GL_UNSIGNED_INT:
			return sizeof(GLint);
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_DOUBLE:
			return sizeof(GLdouble);
		case GL_FIXED:
			return sizeof(GLfixed);
		case GL_HALF_FLOAT:
			return sizeof(GLhalf);
	}

	LOG("warning: unknown opengl type constant: %i", type);

	return 0;
}

void apply_buffer_schema(BufferSchema schema) {
	i64 size = 0;
	for (u64 i = 0; i < schema.num; i++) {
		Attribute *attribute = &schema.attributes[i];
		size += attribute->components * sizeof_gltype(attribute->datatype);
	}

	u64 offset = 0;
	for (u64 i = 0; i < schema.num; i++) {
		Attribute *attribute = &schema.attributes[i];
		glVertexAttribPointer(
			i,
			attribute->components,
			attribute->datatype,
			GL_FALSE,
			size,
			(void *)offset
		);

		if (attribute->enabled) {
			glEnableVertexAttribArray(i);
		} else {
			glDisableVertexAttribArray(i);
		}

		offset += attribute->components * sizeof_gltype(attribute->datatype);
	}
}
