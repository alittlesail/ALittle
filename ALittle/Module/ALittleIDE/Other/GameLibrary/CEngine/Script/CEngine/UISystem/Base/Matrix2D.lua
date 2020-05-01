-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __cos = Math_Cos
local __sin = Math_Sin
Matrix2D = Lua.Class(nil, "ALittle.Matrix2D")

function Matrix2D:Ctor()
	local m = {}
	m[0] = {}
	m[1] = {}
	m[2] = {}
	___rawset(self, "_m", m)
	self:SetIdentity()
end

function Matrix2D:SetIdentity()
	local m = self._m
	m[0][0] = 1
	m[0][1] = 0
	m[0][2] = 0
	m[1][0] = 0
	m[1][1] = 1
	m[1][2] = 0
	m[2][0] = 0
	m[2][1] = 0
	m[2][2] = 1
end

function Matrix2D:SetRotate(rad)
	local m = self._m
	m[0][0] = __cos(rad)
	m[0][1] = __sin(rad)
	m[0][2] = 0
	m[1][0] = -m[0][1]
	m[1][1] = m[0][0]
	m[1][2] = 0
	m[2][0] = 0
	m[2][1] = 0
	m[2][2] = 1
end

function Matrix2D:Rotate(rad)
	local m = Matrix2D()
	m:SetRotate(rad)
	self:Multiply(m)
end

function Matrix2D:SetTranslation(x, y)
	local m = self._m
	m[0][0] = 1
	m[0][1] = 0
	m[0][2] = 0
	m[1][0] = 0
	m[1][1] = 1
	m[1][2] = 0
	m[2][0] = x
	m[2][1] = y
	m[2][2] = 1
end

function Matrix2D:Translation(x, y)
	local m = Matrix2D()
	m:SetTranslation(x, y)
	self:Multiply(m)
end

function Matrix2D:SetScale(x, y)
	local m = self._m
	m[0][0] = x
	m[0][1] = 0
	m[0][2] = 0
	m[1][0] = 0
	m[1][1] = y
	m[1][2] = 0
	m[2][0] = 0
	m[2][1] = 0
	m[2][2] = 1
end

function Matrix2D:Scale(x, y)
	local m = Matrix2D()
	m:SetScale(x, y)
	self:Multiply(m)
end

function Matrix2D:Multiply(right)
	local r = {}
	local m = self._m
	local rm = right._m
	r[0] = {}
	r[0][0] = m[0][0] * rm[0][0] + m[0][1] * rm[1][0] + m[0][2] * rm[2][0]
	r[0][1] = m[0][0] * rm[0][1] + m[0][1] * rm[1][1] + m[0][2] * rm[2][1]
	r[0][2] = m[0][0] * rm[0][2] + m[0][1] * rm[1][2] + m[0][2] * rm[2][2]
	r[1] = {}
	r[1][0] = m[1][0] * rm[0][0] + m[1][1] * rm[1][0] + m[1][2] * rm[2][0]
	r[1][1] = m[1][0] * rm[0][1] + m[1][1] * rm[1][1] + m[1][2] * rm[2][1]
	r[1][2] = m[1][0] * rm[0][2] + m[1][1] * rm[1][2] + m[1][2] * rm[2][2]
	r[2] = {}
	r[2][0] = m[2][0] * rm[0][0] + m[2][1] * rm[1][0] + m[2][2] * rm[2][0]
	r[2][1] = m[2][0] * rm[0][1] + m[2][1] * rm[1][1] + m[2][2] * rm[2][1]
	r[2][2] = m[2][0] * rm[0][2] + m[2][1] * rm[1][2] + m[2][2] * rm[2][2]
	self._m = r
end

Vector2D = Lua.Class(nil, "ALittle.Vector2D")

function Vector2D:Ctor(xx, yy)
	___rawset(self, "_x", xx)
	___rawset(self, "_y", yy)
end

function Vector2D:Multiply(right)
	local rm = right._m
	local xx = self._x * rm[0][0] + self._y * rm[1][0] + 1 * rm[2][0]
	local yy = self._x * rm[0][1] + self._y * rm[1][1] + 1 * rm[2][1]
	self._x = xx
	self._y = yy
end

