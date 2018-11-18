///-------------------------------------------------------------------------------------------------
/// File:	RenderableGroup.h.
///
/// Summary:	Declares the renderable group auxillary class.
///-------------------------------------------------------------------------------------------------

#ifndef __RENDERABLE_GROUP_H__
#define __RENDERABLE_GROUP_H__

#include "Material.h"

struct VertexArray;


using RenderableGroupID = uint32_t;



/// Summary:
/// A render group is a set of renderables that share common properties like the same shader and shape.
/// A RenderableGroup has an ID that is the product of the merged ShapeID and MaterialID of a renderable.
/// It also has an Vertex Array Object holding the appropriate OpenGL state. 
struct RenderableGroup
{
	const RenderableGroupID		m_GroupID;
	const VertexArray*			m_VertexArray;
	
	Material					m_Material;

	RenderableGroup(const RenderableGroupID groupID) :
		m_GroupID(groupID),
		m_VertexArray(new VertexArray),
		m_Material(nullptr)
	{}

	RenderableGroup(const RenderableGroupID groupID, Material material) :
		m_GroupID(groupID),
		m_VertexArray(new VertexArray),
		m_Material(material)
	{}

	void Delete() const
	{
		delete this->m_VertexArray;
	}

	bool operator==(const RenderableGroup &other) const
	{
		return this->m_GroupID == other.m_GroupID;
	}
};

namespace std
{
	template <>
	struct hash<RenderableGroup>
	{
		std::size_t operator()(const RenderableGroup& renderableGroup) const
		{
			return renderableGroup.m_GroupID;
		}
	};

} // namespace std

#endif // __RENDERABLE_GROUP_H__
