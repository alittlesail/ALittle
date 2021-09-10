
#include "Carp/carp_audio_conversion.hpp"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("param: src_path, dst_path\n");
		return -1;
	}

	auto error = CarpAudioConversion::Conversion(argv[1], argv[2]);
	switch (error)
	{
	case CarpAudioConversion::ConversionError::OK:
		printf("conversion succeed\n");
		break;
	case CarpAudioConversion::ConversionError::SRC_FILE_OPEN_FAILED:
		printf("src file open failed!\n");
		break;
	case CarpAudioConversion::ConversionError::DST_FILE_OPEN_FAILED:
		printf("dst file open failed!\n");
		break;
	case CarpAudioConversion::ConversionError::DECODER_CREATE_FAILED:
		printf("decoder create failed!\n");
		break;
	case CarpAudioConversion::ConversionError::ENCODER_CREATE_FAILED:
		printf("encoder create failed!\n");
		break;
	case CarpAudioConversion::ConversionError::DECODER_READ_FILE_FAILED:
		printf("decoder read file failed!\n");
		break;
	case CarpAudioConversion::ConversionError::DECODER_READ_HEAD_FAILED:
		printf("decoder read head failed!\n");
		break;
	case CarpAudioConversion::ConversionError::DECODER_DECODE_FAILED:
		printf("decoder decode failed!\n");
		break;
	default:
		break;
	}
	return static_cast<int>(error);
}
