#pragma once

#include "DirectXTK\SimpleMath.h"

namespace wi {
	namespace Math = DirectX::SimpleMath;

	typedef DirectX::XMFLOAT4   Rectf;
	typedef DirectX::XMFLOAT4   Offset;

	typedef DirectX::XMFLOAT4   float4;
	typedef DirectX::XMFLOAT3   float3;
	typedef DirectX::XMFLOAT2   float2;
	typedef DirectX::XMFLOAT4X4 float4x4;

	// XMVLOAT3 Helpers
	inline XMFLOAT3 operator+ (const XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator+ (const XMFLOAT3& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator- (const XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator- (const XMFLOAT3& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator* (const XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorMultiply(V1, V2);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator* (const XMFLOAT3& v1, const float s) noexcept
	{
		const XMVECTOR V = XMLoadFloat3(&v1);
		const XMVECTOR X = XMVectorScale(V, s);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator* (const float s, const XMFLOAT3& v1) noexcept
	{
		const XMVECTOR V = XMLoadFloat3(&v1);
		const XMVECTOR X = XMVectorScale(V, s);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator/ (const XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorDivide(V1, V2);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3 operator/ (const XMFLOAT3& v1, const float d) noexcept
	{
		const XMVECTOR V = XMLoadFloat3(&v1);
		const XMVECTOR X = XMVectorScale(V, 1.0f / d);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3& operator+= (XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMStoreFloat3(&v1, X);
		return v1;
	}

	inline XMFLOAT3& operator-= (XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMStoreFloat3(&v1, X);
		return v1;
	}

	inline XMFLOAT3& operator*= (XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorMultiply(V1, V2);
		XMStoreFloat3(&v1, X);
		return v1;
	}

	inline XMFLOAT3& operator*= (XMFLOAT3& v, const float s) noexcept
	{
		const XMVECTOR V = XMLoadFloat3(&v);
		const XMVECTOR X = XMVectorScale(V, s);
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3& operator/= (XMFLOAT3& v1, const XMFLOAT3& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat3(&v2);
		const XMVECTOR X = XMVectorDivide(V1, V2);
		XMStoreFloat3(&v1, X);
		return v1;
	}

	inline XMFLOAT3& operator/= (XMFLOAT3& v1, const float d) noexcept
	{
		const XMVECTOR V = XMLoadFloat3(&v1);
		const XMVECTOR X = XMVectorScale(V, 1.0f / d);
		XMFLOAT3 v;
		XMStoreFloat3(&v, X);
		return v;
	}

	inline XMFLOAT3& operator+= (XMFLOAT3& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMStoreFloat3(&v1, X);
		return v1;
	}

	inline XMFLOAT3& operator-= (XMFLOAT3& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat3(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMStoreFloat3(&v1, X);
		return v1;
	}

	// XMVLOAT2 Helpers
	inline XMFLOAT2 operator+ (const XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2 operator- (const XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2 operator* (const XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorMultiply(V1, V2);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2 operator* (const XMFLOAT2& v1, const float s) noexcept
	{
		const XMVECTOR V = XMLoadFloat2(&v1);
		const XMVECTOR X = XMVectorScale(V, s);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2 operator* (const float s, const XMFLOAT2& v1) noexcept
	{
		const XMVECTOR V = XMLoadFloat2(&v1);
		const XMVECTOR X = XMVectorScale(V, s);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2 operator/ (const XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorDivide(V1, V2);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2 operator/ (const XMFLOAT2& v1, const float d) noexcept
	{
		const XMVECTOR V = XMLoadFloat2(&v1);
		const XMVECTOR X = XMVectorScale(V, 1.0f / d);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2& operator+= (XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMStoreFloat2(&v1, X);
		return v1;
	}

	inline XMFLOAT2& operator-= (XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMStoreFloat2(&v1, X);
		return v1;
	}

	inline XMFLOAT2& operator*= (XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorMultiply(V1, V2);
		XMStoreFloat2(&v1, X);
		return v1;
	}

	inline XMFLOAT2& operator*= (XMFLOAT2& v, const float s) noexcept
	{
		const XMVECTOR V = XMLoadFloat2(&v);
		const XMVECTOR X = XMVectorScale(V, s);
		XMStoreFloat2(&v, X);
		return v;
	}

	inline XMFLOAT2& operator/= (XMFLOAT2& v1, const XMFLOAT2& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat2(&v1);
		const XMVECTOR V2 = XMLoadFloat2(&v2);
		const XMVECTOR X = XMVectorDivide(V1, V2);
		XMStoreFloat2(&v1, X);
		return v1;
	}

	inline XMFLOAT2& operator/= (XMFLOAT2& v1, const float d) noexcept
	{
		const XMVECTOR V = XMLoadFloat2(&v1);
		const XMVECTOR X = XMVectorScale(V, 1.0f / d);
		XMFLOAT2 v;
		XMStoreFloat2(&v, X);
		return v;
	}

	// XMVLOAT4 Helpers
	inline XMFLOAT4 operator+ (const XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4 operator- (const XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4 operator* (const XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorMultiply(V1, V2);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4 operator* (const XMFLOAT4& v1, const float s) noexcept
	{
		const XMVECTOR V = XMLoadFloat4(&v1);
		const XMVECTOR X = XMVectorScale(V, s);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4 operator* (const float s, const XMFLOAT4& v1) noexcept
	{
		const XMVECTOR V = XMLoadFloat4(&v1);
		const XMVECTOR X = XMVectorScale(V, s);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4 operator/ (const XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorDivide(V1, V2);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4 operator/ (const XMFLOAT4& v1, const float d) noexcept
	{
		const XMVECTOR V = XMLoadFloat4(&v1);
		const XMVECTOR X = XMVectorScale(V, 1.0f / d);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4& operator+= (XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorAdd(V1, V2);
		XMStoreFloat4(&v1, X);
		return v1;
	}

	inline XMFLOAT4& operator-= (XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorSubtract(V1, V2);
		XMStoreFloat4(&v1, X);
		return v1;
	}

	inline XMFLOAT4& operator*= (XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorMultiply(V1, V2);
		XMStoreFloat4(&v1, X);
		return v1;
	}

	inline XMFLOAT4& operator*= (XMFLOAT4& v, const float s) noexcept
	{
		const XMVECTOR V = XMLoadFloat4(&v);
		const XMVECTOR X = XMVectorScale(V, s);
		XMStoreFloat4(&v, X);
		return v;
	}

	inline XMFLOAT4& operator/= (XMFLOAT4& v1, const XMFLOAT4& v2) noexcept
	{
		const XMVECTOR V1 = XMLoadFloat4(&v1);
		const XMVECTOR V2 = XMLoadFloat4(&v2);
		const XMVECTOR X = XMVectorDivide(V1, V2);
		XMStoreFloat4(&v1, X);
		return v1;
	}

	inline XMFLOAT4& operator/= (XMFLOAT4& v1, const float d) noexcept
	{
		const XMVECTOR V = XMLoadFloat4(&v1);
		const XMVECTOR X = XMVectorScale(V, 1.0f / d);
		XMFLOAT4 v;
		XMStoreFloat4(&v, X);
		return v;
	}
}