#pragma once

namespace Engine {

	class EUUID
	{
	public:
		EUUID();
		// the bits are reversed
		//	for example:
		//	{09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
		//	'975DE909' 'd5434C36' '4CFFDF8A' 'A741ECE0'
		EUUID(u32  a, u32  b, u32  c, u32  d);
		// copy the bytes one by one
		EUUID(const EUUID& src);
		~EUUID();

		EUUID& operator=(const EUUID& src);
		bool		operator==(const EUUID& id) const;
		bool		operator!=(const EUUID& id) const;
		bool    	operator < (const EUUID& iid) const;

		EString			ToString() const;
		bool			FromString(const EString& id);


		// create four 32 Bit integer from the components of the GUID structure
		// the bits are reversed
		//	for example:
		//	{09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
		//	'975DE909' 'd5434C36' '4CFFDF8A' 'A741ECE0'
		void			GetUUID(u32& out1, u32& out2, u32& out3, u32& out4) const;
		const EUUID& CreateNew();
		bool 			IsValid() const;
		const u8* GetData() const;
		u8* GetData();
	protected:
		// {09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
		u8		fData[16];
	public:

		static std::map<const char*, u32> TestMap;
	};

}