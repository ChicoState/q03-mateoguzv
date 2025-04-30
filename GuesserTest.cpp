/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};



TEST(GuesserTest, WrongGuessWithSmallDistanceDecreasesRemaining){
    Guesser g("hello");
    ASSERT_FALSE(g.match("hella")); 
    ASSERT_EQ(2,g.remaining());
}

TEST(GuesserTest, WrongGuessWithBigDistanceLocksOut)
{
    Guesser g("hello");
    ASSERT_FALSE(g.match("xxxxx")); 
    ASSERT_FALSE(g.match("hello")); 
    ASSERT_EQ(3, g.remaining()); 

}

TEST(GuesserTest,LockedOutAfterThreeWrongSmallDistanceGuesses){
    Guesser g("code");
    g.match("cade"); 
     g.match("cade");  
    g.match("cade"); 
 
    ASSERT_FALSE(g.match("code"));
      ASSERT_EQ(0, g.remaining());

}

TEST(GuesserTest,DistanceExactMatchIsZero){
    Guesser g("test" );
    ASSERT_EQ(0,g.distance("test"));
}

TEST(GuesserTest, DistanceOneWrongCharacter){
    	Guesser g("test");
    ASSERT_EQ(1, g.distance("tent"));
}

TEST(GuesserTest,DistanceLongGuessCapped){
    Guesser g("short");
    ASSERT_EQ(5, g.distance("averyverylongstringthatexceeds")); 
}

TEST(GuesserTest, DistanceShortGuessAddsMissing){
    Guesser g("secret");
     ASSERT_EQ(3,g.distance("sec"));
}

TEST(GuesserTest, SecretTruncatedTo32Chars){
    std::string long_secret(100, 'x');
    Guesser g(long_secret);
     ASSERT_EQ(0,g.distance(std::string(32, 'x'))); 
}

TEST(GuesserTest, MatchFailsIfLocked){
    Guesser g("secure");
    g.match("wrongwrongwrong"); 
    ASSERT_FALSE(g.match("secure")); 
}


