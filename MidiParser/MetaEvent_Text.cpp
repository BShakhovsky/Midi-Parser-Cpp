# include "stdafx.h"
# include "MetaEvent_Text.h"
# include "IFileParser.h"
# include "MidiStruct.h"

# pragma warning(push)
#	ifdef _DEBUG
#		pragma warning(disable:4702)	// unreachable code (but may become reachable by mistake \
										// ==> test it)
#	endif
void MetaEvent_Text::Read_impl()
{
	switch (GetChunk()->metaType)
	{
	case 0x00: if (2 != GetInputFile()->PeekByte()) WARNING("Wrong sequence chunk length");
				ReadText("Sequence number");	break;
	case 0x01:	ReadText("Text event");			break;
	case 0x02:	ReadText("Copyright notice");	break;
	case 0x03:	ReadText("Sequence name");		break;
	case 0x04:	ReadText("Instrument name");	break;
	case 0x05:	ReadText("Lyric text");			break;
	case 0x06:	ReadText("Marker text");		break;
	case 0x07:	ReadText("Cue point");			break;
	default: assert("WRONG META TYPE");
	}
}
# pragma warning(pop)

void MetaEvent_Text::ReadText(const char* eventMsg)
{
	const auto length = GetInputFile()->ReadVarLenFormat();		// may throw
	if (length > 0xFF) WARNING("Max 256 byts and ISO-8859-1 character set allowed");
	std::vector<char> result(length + 1);						// + zero-byte in the end
	GetInputFile()->ReadData(result.data(), length);

	if (strcmp(eventMsg, "Sequence name") == 0) SetTrackName(result.data());
	else if (strcmp(eventMsg, "Marker text") == 0)
		AppendLog((boost::format{ "\t\"%1%\"\n" } % result.data()).str().c_str());
	else AppendLog((boost::format{ "%1% \"%2%\"\n" } %			// not covered by unit tests
		eventMsg % result.data()).str().c_str());
}