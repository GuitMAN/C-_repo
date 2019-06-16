#pragma once
#include "IBase.h"
#include "../scr/core/Vector3f.h"
#include "../scr/core/Vector2f.h"

namespace Sam3d {



	class IMeshBuffer : public virtual IBase
	{
	public:

		//! Get the material of this meshbuffer
		/** \return Material of this buffer. */
//		virtual SMaterial& getMaterial() = 0;

		//! Get the material of this meshbuffer
		/** \return Material of this buffer. */
//		virtual const SMaterial& getMaterial() const = 0;

		//! Get type of vertex data which is stored in this meshbuffer.
		/** \return Vertex type of this buffer. */
//		virtual E_VERTEX_TYPE getVertexType() const = 0;

		//! Get access to vertex data. The data is an array of vertices.
		/** Which vertex type is used can be determined by getVertexType().
		\return Pointer to array of vertices. */
		virtual const void* getVertices() const = 0;

		//! Get access to vertex data. The data is an array of vertices.
		/** Which vertex type is used can be determined by getVertexType().
		\return Pointer to array of vertices. */
		virtual void* getVertices() = 0;

		//! Get amount of vertices in meshbuffer.
		/** \return Number of vertices in this buffer. */
		virtual uInt getVertexCount() const = 0;

		//! Get type of index data which is stored in this meshbuffer.
		/** \return Index type of this buffer. */
//		virtual E_INDEX_TYPE getIndexType() const = 0;

		//! Get access to indices.
		/** \return Pointer to indices array. */
		virtual const uShort* getIndices() const = 0;

		//! Get access to indices.
		/** \return Pointer to indices array. */
		virtual uShort* getIndices() = 0;

		//! Get amount of indices in this meshbuffer.
		/** \return Number of indices in this buffer. */
		virtual uInt getIndexCount() const = 0;

		//! Get the axis aligned bounding box of this meshbuffer.
		/** \return Axis aligned bounding box of this buffer. */
//		virtual const aabbox3df& getBoundingBox() const = 0;

		//! Set axis aligned bounding box
		/** \param box User defined axis aligned bounding box to use
		for this buffer. */
//		virtual void setBoundingBox(const core::aabbox3df& box) = 0;

		//! Recalculates the bounding box. Should be called if the mesh changed.
		virtual void recalculateBoundingBox() = 0;

		//! returns position of vertex i
		virtual const Vector3f& getPosition(uInt i) const = 0;

		//! returns position of vertex i
		virtual Vector3f& getPosition(uInt i) = 0;

		//! returns normal of vertex i
		virtual const Vector3f& getNormal(uInt i) const = 0;

		//! returns normal of vertex i
		virtual Vector3f& gtNormal(uInt i) = 0;

		//! returns texture coord of vertex i
		virtual const Vector2f& getTCoords(uInt i) const = 0;

		//! returns texture coord of vertex i
		virtual Vector2f& getTCoords(uInt i) = 0;

		//! Append the vertices and indices to the current buffer
		/** Only works for compatible vertex types.
		\param vertices Pointer to a vertex array.
		\param numVertices Number of vertices in the array.
		\param indices Pointer to index array.
		\param numIndices Number of indices in array. */
		virtual void append(const void* const vertices, uInt numVertices, const uShort* const indices, uInt numIndices) = 0;

		//! Append the meshbuffer to the current buffer
		/** Only works for compatible vertex types
		\param other Buffer to append to this one. */
		virtual void append(const IMeshBuffer* const other) = 0;

		//! get the current hardware mapping hint
//		virtual E_HARDWARE_MAPPING getHardwareMappingHint_Vertex() const = 0;

		//! get the current hardware mapping hint
//		virtual E_HARDWARE_MAPPING getHardwareMappingHint_Index() const = 0;

		//! set the hardware mapping hint, for driver
//		virtual void setHardwareMappingHint(E_HARDWARE_MAPPING newMappingHint, E_BUFFER_TYPE buffer = EBT_VERTEX_AND_INDEX) = 0;

		//! flags the meshbuffer as changed, reloads hardware buffers
//		virtual void setDirty(E_BUFFER_TYPE buffer = EBT_VERTEX_AND_INDEX) = 0;

		//! Get the currently used ID for identification of changes.
		/** This shouldn't be used for anything outside the VideoDriver. */
		virtual uInt getChangedID_Vertex() const = 0;

		//! Get the currently used ID for identification of changes.
		/** This shouldn't be used for anything outside the VideoDriver. */
		virtual uInt getChangedID_Index() const = 0;

		//! Describe what kind of primitive geometry is used by the meshbuffer
		/** Note: Default is EPT_TRIANGLES. Using other types is fine for rendering.
		But meshbuffer manipulation functions might expect type EPT_TRIANGLES
		to work correctly. Also mesh writers will generally fail (badly!) with other
		types than EPT_TRIANGLES. */
//		virtual void setPrimitiveType(E_PRIMITIVE_TYPE type) = 0;

		//! Get the kind of primitive geometry which is used by the meshbuffer
//		virtual E_PRIMITIVE_TYPE getPrimitiveType() const = 0;

		//! Calculate how many geometric primitives are used by this meshbuffer
		virtual uInt getPrimitiveCount() const
		{
/*			uInt indexCount = getIndexCount();
			switch (getPrimitiveType())
			{
			case EPT_POINTS:	        return indexCount;
			case scene::EPT_LINE_STRIP:     return indexCount - 1;
			case scene::EPT_LINE_LOOP:      return indexCount;
			case scene::EPT_LINES:          return indexCount / 2;
			case scene::EPT_TRIANGLE_STRIP: return (indexCount - 2);
			case scene::EPT_TRIANGLE_FAN:   return (indexCount - 2);
			case scene::EPT_TRIANGLES:      return indexCount / 3;
			case scene::EPT_QUAD_STRIP:     return (indexCount - 2) / 2;
			case scene::EPT_QUADS:          return indexCount / 4;
			case scene::EPT_POLYGON:        return indexCount; // (not really primitives, that would be 1, works like line_strip)
			case scene::EPT_POINT_SPRITES:  return indexCount;
			}
			*/
			return 0;
		}

	};
}