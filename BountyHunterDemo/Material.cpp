///-------------------------------------------------------------------------------------------------
/// File:	Material.cpp.
///
/// Summary:	Implements the material class.
///-------------------------------------------------------------------------------------------------

#include "Material.h"

Material::Material(IMaterial* material) :
	m_materialData(material)
{}

Material::~Material()
{
	this->m_materialData = nullptr;
}