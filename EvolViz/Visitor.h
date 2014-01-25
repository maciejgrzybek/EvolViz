#pragma once
namespace common
{

template<typename... Types>
struct Visitor;

template<typename First, typename... Types>
struct Visitor<First, Types...> : Visitor<Types...>
{
	using Visitor<Types...>::visit;
	virtual void visit(const First&) = 0;
};

template<typename First>
struct Visitor<First>
{
	virtual void visit(const First&) = 0;
};

} // namespace common