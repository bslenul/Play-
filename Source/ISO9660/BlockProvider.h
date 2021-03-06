#pragma once

#include <memory>
#include "Types.h"
#include "Stream.h"

namespace ISO9660
{
	class CBlockProvider
	{
	public:
		enum BLOCKSIZE
		{
			BLOCKSIZE = 0x800ULL
		};

		virtual ~CBlockProvider() = default;
		virtual void ReadBlock(uint32, void*) = 0;
	};

	class CBlockProvider2048 : public CBlockProvider
	{
	public:
		typedef std::shared_ptr<Framework::CStream> StreamPtr;

		CBlockProvider2048(const StreamPtr& stream, uint32 offset = 0)
		    : m_stream(stream)
		    , m_offset(offset)
		{
		}

		void ReadBlock(uint32 address, void* block) override
		{
			m_stream->Seek(static_cast<uint64>(address + m_offset) * BLOCKSIZE, Framework::STREAM_SEEK_SET);
			m_stream->Read(block, BLOCKSIZE);
		}

	private:
		StreamPtr m_stream;
		uint32 m_offset = 0;
	};

	class CBlockProviderCDROMXA : public CBlockProvider
	{
	public:
		typedef std::shared_ptr<Framework::CStream> StreamPtr;

		CBlockProviderCDROMXA(const StreamPtr& stream)
		    : m_stream(stream)
		{
		}

		void ReadBlock(uint32 address, void* block) override
		{
			m_stream->Seek((static_cast<uint64>(address) * INTERNAL_BLOCKSIZE) + BLOCKHEADER_SIZE, Framework::STREAM_SEEK_SET);
			m_stream->Read(block, BLOCKSIZE);
		}

	private:
		enum
		{
			INTERNAL_BLOCKSIZE = 0x930ULL,
			BLOCKHEADER_SIZE = 0x18ULL
		};

		StreamPtr m_stream;
	};
}
