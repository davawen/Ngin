#pragma once

#include <stdbool.h>

#include "types.h"

typedef struct {
	/// Symbolic macro datatype of the attribute (GL_INT, GL_FLOAT, etc...)
	GLenum datatype;
	/// Number of components if it's a vector, 1 otherwise
	u32 components;
	/// Wether this attribute should be enabled
	bool enabled;
} Attribute;

/// Struct used to describe the schema of attributes given to a shader/the shape of a buffer
typedef struct {
	/// Number of attributes
	u32 num;
	Attribute *attributes;
} BufferSchema;

/// Buffer schema for a vertex shader taking in one vec3 as an argument
extern const BufferSchema simple_vertex_schema;

/// Applies the given buffer schema to the curently bound vertex array
void apply_buffer_schema(BufferSchema schema);
