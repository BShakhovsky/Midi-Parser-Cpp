# include "stdafx.h"
# include "..\MidiParser\MidiStruct.h"

using MidiStruct::ChunkType;

TEST(MidiStructure, BoolOperators)
{
	ChunkType
		header{ 'M', 'T', 'h', 'd' },
		track{ 'M', 'T', 'r', 'k' },
		anotherHeader{ 'M', 'T', 'h', 'd' };
	ASSERT_TRUE(header == anotherHeader);
	ASSERT_FALSE(header != anotherHeader);
	ASSERT_FALSE(header == track);
	ASSERT_TRUE(header != track);
}