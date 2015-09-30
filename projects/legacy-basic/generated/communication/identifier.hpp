// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding XML file instead.
 */
// ----------------------------------------------------------------------------

#ifndef	ROBOT_IDENTIFIER_HPP
#define	ROBOT_IDENTIFIER_HPP

namespace robot
{
	namespace domain
	{
		enum Identifier
		{
		};
				
		inline const char* 
		enumToString(Identifier e)
		{
			switch (e)
			{
				default: return "__UNKNOWN_DOMAIN__";
			}
		}
	}
	
	namespace component
	{
		enum Identifier
		{
			SENDER = 0x01,
			RECEIVER = 0x02,
		};
				
		inline const char* 
		enumToString(Identifier e)
		{
			switch (e)
			{
				case SENDER: return "SENDER";
				case RECEIVER: return "RECEIVER";
				default: return "__UNKNOWN_COMPONENT__";
			}
		}
	}
	
	namespace action
	{
		enum Identifier
		{
			SET_POSITION = 0x01,
			GET_POSITION = 0x02,
		};
				
		inline const char* 
		enumToString(Identifier e)
		{
			switch (e)
			{
				case SET_POSITION: return "SET_POSITION";
				case GET_POSITION: return "GET_POSITION";
				default: return "__UNKNOWN_ACTION__";
			}
		}
	}
		
	namespace event
	{
		enum Identifier
		{
		};
		
		inline const char* 
		enumToString(Identifier e)
		{
			switch (e)
			{
				default: return "__UNKNOWN_EVENT__";
			}
		}
	}
}	// namespace robot

#endif	// ROBOT_IDENTIFIER_HPP
