#ifndef _MPEG_HEADER_H_
#define _MPEG_HEADER_H_


typedef unsigned int uint;


// Declarations
enum CHANNEL_MODE
{
	CHANNEL_STEREO = 0,
	CHANNEL_JOINT_STEREO,
	CHANNEL_DUAL,
	CHANNEL_MONO
};

enum EMPHASIS
{
	EMPHASIS_NONE,
	EMPHASIS_50_15,
	EMPHASIS_CCIT_J17
};

// MPEG version
class CMPEGVer
{
public:
	CMPEGVer();
	CMPEGVer(uint f_mask);

	bool isValid()	const;
	bool isV2()		const;

	uint getIndex()	const;

private:
	void init(uint f_mask);

private:
	bool m_v2;
	bool m_v25;
};

// MPEG header
class CMPEGHeader
{
public:
	CMPEGHeader(uint f_header);

	// Basic
	bool isValid() const;

	const CMPEGVer&	getMpegVersion()	const;
	uint			getLayer()			const;
	uint			getBitrate()		const;
	uint			getFrequency()		const;

	bool			isProtected()		const;
	bool			isPadded()			const;
	bool			isPrivate()			const;
	bool			isCopyrighted()		const;
	bool			isOriginal()		const;

	EMPHASIS		getEmphasis()		const;
	CHANNEL_MODE	getChannelMode()	const;

	// Complex
	uint	getFrameSize()		const;
	float	getFrameLength()	const;

	uint getNextFrame() const;

	// version, layer, sampling rate, channel mode, emphasis (________ ___xxxx_ ____xx__ xx____xx)
	bool operator==(const CMPEGHeader& f_header) const;
	bool operator!=(const CMPEGHeader& f_header) const;

	// XING / VBRI header is in the 1-st frame after side information block (layer 3 only)

// Private members
private:
	CMPEGHeader();

	bool isValidInternal() const;

	CMPEGVer	calcMpegVersion()									const;
	uint		calcLayer()											const;
	uint		calcBitrate(const CMPEGVer& f_ver, uint f_layer)	const;
	uint		calcFrequency(const CMPEGVer& f_ver)				const;

	uint getSideInfoSize() const;

private:
	uint m_header;

	bool m_valid;

	CMPEGVer m_mpeg;
	uint m_layer;
	uint m_bitrate;
	uint m_frequency;
};

#endif	// _MPEG_HEADER_H_
