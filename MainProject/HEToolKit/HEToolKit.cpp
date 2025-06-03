#include "HEToolKit.h"

//bool wi::scene::Raycast(XMFLOAT3 origin, XMFLOAT3 direction, float maxDistance, const uint32_t layerMask, const Scene& scene)
//{
//	if (scene.objects.GetCount() <= 0)
//		return false;
//
//	wi::primitive::Ray ray(origin, direction);
//	const XMVECTOR rayOrigin    = XMLoadFloat3(&origin);
//	const XMVECTOR rayDirection = XMVector3Normalize(XMLoadFloat3(&direction));
//	for (size_t i = 0; i < scene.aabb_objects.size(); ++i)
//	{
//		const wi::primitive::AABB& aabb = scene.aabb_objects[i];
//		if (!(aabb.layerMask & layerMask))
//			continue;
//		if (!ray.intersects(aabb))
//			continue;
//
//		const ObjectComponent& object = scene.objects[i];
//		if (object.meshID == wi::ecs::INVALID_ENTITY)
//			continue;
//
//		const MeshComponent& mesh = *scene.meshes.GetComponent(object.meshID);
//		const SoftBodyPhysicsComponent* softbody = scene.softbodies.GetComponent(object.meshID);
//		const bool softbody_active = softbody != nullptr && !softbody->vertex_positions_simulation.empty();
//
//		const XMMATRIX objectMat = XMLoadFloat4x4(&scene.matrix_objects[i]);
//		const XMMATRIX objectMat_Inverse = XMMatrixInverse(nullptr, objectMat);
//
//		const XMVECTOR rayOrigin_local = XMVector3Transform(rayOrigin, objectMat_Inverse);
//		const XMVECTOR rayDirection_local = XMVector3Normalize(XMVector3TransformNormal(rayDirection, objectMat_Inverse));
//
//		const ArmatureComponent* armature = mesh.IsSkinned() ? scene.armatures.GetComponent(mesh.armatureID) : nullptr;
//
//		uint32_t first_subset = 0;
//		uint32_t last_subset  = 0;
//		mesh.GetLODSubsetRange(0, first_subset, last_subset);
//		for (uint32_t subsetIndex = first_subset; subsetIndex < last_subset; ++subsetIndex)
//		{
//			const MeshComponent::MeshSubset& subset = mesh.subsets[subsetIndex];
//			for (size_t i = 0; i < subset.indexCount; i += 3)
//			{
//				const uint32_t i0 = mesh.indices[subset.indexOffset + i + 0];
//				const uint32_t i1 = mesh.indices[subset.indexOffset + i + 1];
//				const uint32_t i2 = mesh.indices[subset.indexOffset + i + 2];
//
//				XMVECTOR p0;
//				XMVECTOR p1;
//				XMVECTOR p2;
//
//				if (softbody_active)
//				{
//					p0 = softbody->vertex_positions_simulation[i0].LoadPOS();
//					p1 = softbody->vertex_positions_simulation[i1].LoadPOS();
//					p2 = softbody->vertex_positions_simulation[i2].LoadPOS();
//				}
//				else
//				{
//					if (armature == nullptr)
//					{
//						p0 = XMLoadFloat3(&mesh.vertex_positions[i0]);
//						p1 = XMLoadFloat3(&mesh.vertex_positions[i1]);
//						p2 = XMLoadFloat3(&mesh.vertex_positions[i2]);
//					}
//					else
//					{
//						p0 = SkinVertex(mesh, *armature, i0);
//						p1 = SkinVertex(mesh, *armature, i1);
//						p2 = SkinVertex(mesh, *armature, i2);
//					}
//				}
//
//				float distance;
//				if (!DirectX::TriangleTests::Intersects(rayOrigin_local, rayDirection_local, p0, p1, p2, distance))
//					continue;
//				const XMVECTOR dir = XMVectorScale(rayDirection_local, distance);
//				const XMVECTOR pos = XMVector3Transform(XMVectorAdd(rayOrigin_local, dir), objectMat);
//				distance = wi::math::Distance(pos, rayOrigin);
//				if (distance <= maxDistance)
//					return true;
//			}
//		}
//	}
//
//	return false;
//}

//float wi::scene::Raycast(XMFLOAT3 origin, XMFLOAT3 direction, const uint32_t layerMask, const Scene& scene)
//{
//	if (scene.objects.GetCount() <= 0)
//		return FLT_MAX;
//
//	float distance = FLT_MAX;
//	wi::primitive::Ray ray(origin, direction);
//	const XMVECTOR rayOrigin    = XMLoadFloat3(&origin);
//	const XMVECTOR rayDirection = XMVector3Normalize(XMLoadFloat3(&direction));
//	for (size_t i = 0; i < scene.aabb_objects.size(); ++i)
//	{
//		const wi::primitive::AABB& aabb = scene.aabb_objects[i];
//		if (!(aabb.layerMask & layerMask))
//			continue;
//		if (!ray.intersects(aabb))
//			continue;
//
//		const ObjectComponent& object = scene.objects[i];
//		if (object.meshID == wi::ecs::INVALID_ENTITY)
//			continue;
//
//		const MeshComponent& mesh = *scene.meshes.GetComponent(object.meshID);
//		const SoftBodyPhysicsComponent* softbody = scene.softbodies.GetComponent(object.meshID);
//		const bool softbody_active = softbody != nullptr && !softbody->vertex_positions_simulation.empty();
//
//		const XMMATRIX objectMat = XMLoadFloat4x4(&scene.matrix_objects[i]);
//		const XMMATRIX objectMat_Inverse = XMMatrixInverse(nullptr, objectMat);
//
//		const XMVECTOR rayOrigin_local = XMVector3Transform(rayOrigin, objectMat_Inverse);
//		const XMVECTOR rayDirection_local = XMVector3Normalize(XMVector3TransformNormal(rayDirection, objectMat_Inverse));
//
//		const ArmatureComponent* armature = mesh.IsSkinned() ? scene.armatures.GetComponent(mesh.armatureID) : nullptr;
//
//		uint32_t first_subset = 0;
//		uint32_t last_subset  = 0;
//		mesh.GetLODSubsetRange(0, first_subset, last_subset);
//		for (uint32_t subsetIndex = first_subset; subsetIndex < last_subset; ++subsetIndex)
//		{
//			const MeshComponent::MeshSubset& subset = mesh.subsets[subsetIndex];
//			for (size_t i = 0; i < subset.indexCount; i += 3)
//			{
//				const uint32_t i0 = mesh.indices[subset.indexOffset + i + 0];
//				const uint32_t i1 = mesh.indices[subset.indexOffset + i + 1];
//				const uint32_t i2 = mesh.indices[subset.indexOffset + i + 2];
//
//				XMVECTOR p0;
//				XMVECTOR p1;
//				XMVECTOR p2;
//
//				if (softbody_active)
//				{
//					p0 = softbody->vertex_positions_simulation[i0].LoadPOS();
//					p1 = softbody->vertex_positions_simulation[i1].LoadPOS();
//					p2 = softbody->vertex_positions_simulation[i2].LoadPOS();
//				}
//				else
//				{
//					if (armature == nullptr)
//					{
//						p0 = XMLoadFloat3(&mesh.vertex_positions[i0]);
//						p1 = XMLoadFloat3(&mesh.vertex_positions[i1]);
//						p2 = XMLoadFloat3(&mesh.vertex_positions[i2]);
//					}
//					else
//					{
//						p0 = SkinVertex(mesh, *armature, i0);
//						p1 = SkinVertex(mesh, *armature, i1);
//						p2 = SkinVertex(mesh, *armature, i2);
//					}
//				}
//
//				float d;
//				if (!DirectX::TriangleTests::Intersects(rayOrigin_local, rayDirection_local, p0, p1, p2, d))
//					continue;
//				const XMVECTOR dir = XMVectorScale(rayDirection_local, d);
//				const XMVECTOR pos = XMVector3Transform(XMVectorAdd(rayOrigin_local, dir), objectMat);
//				d = wi::math::Distance(pos, rayOrigin);
//				if (d < distance)
//					distance = d;
//			}
//		}
//	}
//
//	return distance;
//}

HE::ECS::Entity wi::scene::LoadModel(Scene& scene, const std::string& fileName, const uint32_t layerMask, const XMMATRIX& transformMatrix, bool attached)
{
	Scene work;
	HE::ECS::Entity root = LoadModel(work, fileName, transformMatrix, attached);

	for (size_t i = 0; i < work.layers.GetCount(); ++i)
		work.layers[i].layerMask = layerMask;

	scene.Merge(work);
	return root;
}