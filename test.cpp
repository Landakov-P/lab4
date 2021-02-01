#include "FundClass/pch.h"
#include "FundClass/apartments.h"
#include "FundClass/room.h"
#include"gtest/gtest.h"

using namespace FundClass;

TEST(Constructors, EmptyDefaultConstructor) 
{
	Apartments ap;
	EXPECT_EQ("undefined", ap.get_street());
	EXPECT_EQ(0, ap.get_countOfRooms());
	EXPECT_EQ(0, ap.get_number());
	EXPECT_EQ(0, ap.get_area());
	Apartments ap2("Mira");
	EXPECT_EQ("Mira", ap2.get_street());
	EXPECT_EQ(0, ap2.get_countOfRooms());
	EXPECT_EQ(0, ap2.get_number());
	EXPECT_EQ(0, ap2.get_area());
}


TEST(Setters, set_number)
{
	Apartments ap("Mira");
	ap.set_number(5);
	EXPECT_EQ(5, ap.get_number());
	EXPECT_THROW(ap.set_number(-1), std::invalid_argument);
}

TEST(Setters, add_delete_select_room)
{
	Apartments ap("Mira");
	ap.set_number(5);
	Room r1("hall");
	r1.set_area(12);
	ap.add_room(r1);
	EXPECT_EQ(1, ap.get_countOfRooms());
	EXPECT_NEAR(12, ap.get_area(), 0.01);
	EXPECT_THROW(ap.select_room(2), std::invalid_argument);
	EXPECT_THROW(ap.select_room(-1), std::invalid_argument);
	EXPECT_EQ("hall", ap.select_room(1).get_name());
	Room r2("kitchen");
	r2.set_remark("This is kitchen").set_area(20);
	ap.add_room(r2);
	EXPECT_EQ(2, ap.get_countOfRooms());
	EXPECT_NEAR(32, ap.get_area(), 0.01);
	EXPECT_EQ("kitchen", ap.select_room(2).get_name());
	EXPECT_EQ("This is kitchen", ap.select_room(2).get_remark());
	EXPECT_THROW(ap.exclude_room(3), std::invalid_argument);
	EXPECT_THROW(ap.exclude_room(-1), std::invalid_argument);
	ap.exclude_room(1);
	EXPECT_EQ(1, ap.get_countOfRooms());
	EXPECT_EQ(20, ap.get_area());
}