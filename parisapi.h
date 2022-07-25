#ifndef ParisAPI_H
#define ParisAPI_H

/*  AIX PARIS API PRELIMINARY DEFINITIONS */

#define PARISVERSION 10000  /* version 1.0000 */

typedef void* VPS_Handle;

typedef unsigned long VPS_AsyncID; 

/* errors are returned in VPS_Status 
 * and defined by VPS_StatusType
 */
typedef int VPS_Status;

/* The number of filed members in structure array elements 
 * will be given using elements defined with VPS_Count  
 */

#define VPS_Count short

/* general defines 
 */

/* structure array size maximum size '#' defines 
 * are given preceding the structure definitions
 */


/* text sizes in structures 
 * the "AxxxxxBxxxxxLength" value is to include the 
 * terminating 0  
 * *** most are now way too large and will be made smaller ****** 
 */ 

typedef enum VPS_Paris_Text_Lengths
{
  VPS_AccountNameLength          =  64,
  VPS_PasswordLength             =  40,
  VPS_AirportLocationLength      =   4,
  VPS_LocationNameLength         =  80,
  VPS_AirLineNameLength          = 120,
  VPS_FlightNumberStringLength   =  24,
  VPS_GateStringLength           =  24,
  VPS_StatusStringLength         = 120,
  VPS_ItinerayNumberStringLength =  16,
  VPS_HotelLocationLength        = 120,
  VPS_HotelNameLength            = 120,
  VPS_RentalCarNameLength        =  60,
  VPS_PolicyViolationLength      =  90,
  VPS_DescriptionStringLength    = 160,
  VPS_PidLength                  =  15
} VPS_ParisTextLengths;

/* condition values
 */

typedef enum VPS_Reserved_Mark
{
  VPS_NowReserved,
  VPS_Unreserved,
  VPS_Unrequested,
} VPS_ReservedMark;


typedef enum VPS_Ticket_Class
{
  VPS_coach,
  VPS_business,
  VPS_first_class
} VPS_TicketClass;

/* meal types
 */

typedef enum VPS_Meal_Type
{
  VPS_None,
  VPS_Breakfast,
  VPS_Lunch,
  VPS_Snack,
  VPS_Dinner 
} VPS_MealType;

/* flight status values (incomplete )
 */

typedef enum VPS_Status_Label
{
  VPS_In_Flight,
  VPS_On_Schedule,
  VPS_Canceled,
  VPS_Arrived_Late,
  VPS_Arrived_Early,
  VPS_Delayed,
}VPS_StatusLabel;

/* one way or round trip
 */

typedef enum VPS_Trip_Type
{
  VPS_OneWay,
  VPS_RoundTrip,
  VPS_MultiLeg,   /* not used */
}VPS_TripType;

/* Flight preferance indication 
 */

typedef enum VPS_Time_Select
{
  Departing_after_hour,
  Arriving_before_hour,
}VPS_TimeSelect;

/* some true/false conditions are bits in a flag type
 */

typedef enum VPS_Flight_Flags
{
  VPS_Policy = 1,
  VPS_Prefered = 2,
  VPS_Negotiated = 4,
}VPS_FlightFlags;

#define VPS_POLICY(a) ( a & VPS_Policy)
#define VPS_PREFERED(a) ( a & VPS_Prefered)
#define VPS_NEGOTIATED(a) (a & VPS_Negotiated)

#define VPS_flags unsigned long

#define VPS_LONGEST_KEY 256  /* way too long now */

typedef struct VPS_Request_Key  /* responce key */
{
  char HtmlPartion[VPS_LONGEST_KEY];   /*as long as the longest key we'll ever need */
} VPS_RequestKey;


/* date and time 
 */

typedef struct VPS_Date_Info
{
  short day;
  short month;         /* 0 is January */
  short year;          /* 4 digit year i.e. 2001 etc. */
}VPS_DateInfo;

/* Time of day is used for laocal times and for flight durations
 */

typedef struct VPS_Time_Of_Day   
{
  short hour;          /* given in 24 hour time */
  short min;
  short extra;         /* when used for flight durations, is used as +1 day, + 2 days*/
}VPS_TimeOfDay;

/* status error types list 
 */

typedef enum VPS_Status_Types
{                                             /* numbers will change use names */
   VPS_OK,                  /* always first and so == 0    0 */
   VPS_LIBRARY_TOO_OLD,     /* always second               1 */
   VPS_SERVER_TOO_OLD,      /* always third                2 */
   VPS_LOGONERROR,
   VPS_NOTINITED,
   VPS_NOTSIGNEDIN,         /*                             5 */
   VPS_WEBCOMMERR, 
   VPS_BADREQUESTKEY,
   VPS_BADLOCATION,
   VPS_INVALIDMATCHDATA,
   VPS_INVALIDDATEORTIME,   /*                             10 */
   VPS_UNSUPORTEDAIRLINE,
   VPS_NOSTATUSAVAILABLE,
   VPS_NOSUCHFLIGHT,
   VPS_RESERVATIONFAILED,
   VPS_LIMITERRORS,         /* always greater than the last real error and last 15 */
}VPS_StatusTypes;

typedef struct VPS_US_Funds
{
   short dollors;
   short cents;
}VPS_USFunds;


/*login dat struct
 */

typedef struct  VPS_Logon_Data
{
     short cPidnum;
     short cPasscode;
}VPS_LogonData;


/* the itinerary(s) are given in a fixed length array  
 */

typedef struct VPS_City_CPart_Country
{
   char cCity[VPS_LocationNameLength];
   char cState[VPS_LocationNameLength];
   char cCountry[VPS_LocationNameLength];
}VPS_CityCPartCountry;

typedef struct VPS_Itinerary_Choice
{
    VPS_RequestKey ViewThisOne;
    VPS_CityCPartCountry AirportLocation;
    VPS_DateInfo  dateplaned;
}VPS_ItineraryChoice;

#define VPS_MAX_ITINERARYCHOICES 20

typedef struct VPS_Itinerary_List
{
  VPS_Count choices_count;
  VPS_ItineraryChoice Itinerary_Choices[VPS_MAX_ITINERARYCHOICES];
}VPS_ItineraryList;


#define VPS_MAX_HOTELRESTRICTIONS 8
#define VPS_MAX_HOTELAMENITIES    4
#define VPS_MAX_HOTELADDRESS      6

typedef struct VPS_Itinerary_Hotel
{
     VPS_DateInfo date;
     VPS_ReservedMark resevation;   
     char cHotelName[VPS_HotelNameLength];
     char cHotelAddress[VPS_MAX_HOTELADDRESS][VPS_DescriptionStringLength];
     VPS_TimeOfDay checkin;
     VPS_TimeOfDay checkOut;
     char cRoomDescription[VPS_DescriptionStringLength];
     VPS_Count amenitiescount;
     char cHotelAmenities[VPS_MAX_HOTELAMENITIES][VPS_DescriptionStringLength];
     VPS_USFunds roomerate;
     VPS_USFunds taxes;
     VPS_Count restrictions_count;
     char cRestrictions[VPS_MAX_HOTELRESTRICTIONS][VPS_DescriptionStringLength];               
}VPS_ItineraryHotel;

typedef struct VPS_Itinerary_Rental_Car
{
  VPS_ReservedMark resevation;   
  char cRentalCompanyName[VPS_RentalCarNameLength];
  char cRentalAddress[VPS_MAX_HOTELADDRESS][VPS_DescriptionStringLength];
  VPS_DateInfo pickupdate;
  VPS_TimeOfDay pickuptime;
  VPS_DateInfo dropoffdate;
  VPS_TimeOfDay dropofftime;
  char cCarDescription[VPS_DescriptionStringLength];
  VPS_USFunds ratecar;
  char cRate[VPS_DescriptionStringLength];
  char cCarConfimationNumber[VPS_DescriptionStringLength];
}VPS_ItineraryRentalCar;

typedef struct VPS_Carrier_Detail_Leg
{
  char cCarrier[VPS_AirLineNameLength];
  char cFlightNumber[VPS_FlightNumberStringLength];
  char cConnectionLocation[VPS_AirportLocationLength];
  char cDepartsFrom[VPS_AirportLocationLength];
  char cArrivesAt[VPS_AirportLocationLength];
  VPS_FlightFlags flags;  
  VPS_TimeOfDay duration;
  VPS_TimeOfDay hour_departure;
  VPS_DateInfo  date_departure;                     
  VPS_TimeOfDay arrival;                         // local time of arrival only
  VPS_MealType Meal;
  VPS_TicketClass tickettype;
  short distanceflown;
  char cPlaneDescriptionSeats[VPS_DescriptionStringLength];
}VPS_CarrierDetailLeg;


#define VPS_MAX_DETAILFLIGHTLEGS 5

typedef struct VPS_Flight_Carrier_Detail
{
  VPS_Count legscount[2];
  VPS_CarrierDetailLeg FlightLegs[2][VPS_MAX_DETAILFLIGHTLEGS];
}VPS_FlightCarrierDetail;

#define VPS_MAX_POLICYRESPONCES 8
#define VPS_MAX_RULESRESTRICTIONS 8
#define VPS_MAX_DETAILHOTELS 5
#define VPS_MAX_DETAILRENTALCARS 5
#define VPS_MAX_DETAILFLIGHTS    5

typedef struct VPS_Itinerary_Details
{
  VPS_ItineraryChoice ItineraryName;
  char cItineraryNumber[VPS_ItinerayNumberStringLength];
  VPS_Flight_Flags flags;
  VPS_ReservedMark Reserved;
  char cDeparts[2][VPS_AirportLocationLength];
  char cArrives[2][VPS_AirportLocationLength];
  VPS_USFunds base_fare;
  VPS_USFunds taxes;  
  VPS_USFunds total_cost;  
  short totaltripmiles[2];
  short totaltriptime[2];
  VPS_Count flightcount[2];
  VPS_Flight_Carrier_Detail Flights[VPS_MAX_DETAILFLIGHTS];
  VPS_Count responcescount;
  char cPoilicyResponces[VPS_MAX_POLICYRESPONCES][VPS_PolicyViolationLength];
  VPS_Count restrictionscount;
  char cRulesRestrictions[VPS_MAX_RULESRESTRICTIONS][VPS_DescriptionStringLength];
  VPS_Count carcount;
  VPS_ItineraryRentalCar cars[VPS_MAX_DETAILRENTALCARS];
  VPS_Count hotelcount;
  VPS_ItineraryHotel hotels[VPS_MAX_DETAILHOTELS];
}VPS_ItineraryDetails;

typedef struct VPS_Flight_Status_Request
{
   char cCarrier[VPS_AirLineNameLength];
   char cFlightNumber[VPS_FlightNumberStringLength];
   VPS_DateInfo date;           
} VPS_FlightStatusRequest;

/* Arrival/Departing Search results 
 */

typedef struct VPS_Flight_Leg
{
    char cDepartsFrom[VPS_AirportLocationLength];
    char cArrivesAt[VPS_AirportLocationLength];
    char cDepartureGate[VPS_GateStringLength];
    char cArrivalGate[VPS_GateStringLength];
    VPS_TimeOfDay departure_time; 
    VPS_TimeOfDay arrives_time;
    VPS_TimeOfDay estimated_departure_time;
    VPS_TimeOfDay estimated_arival_time;
    VPS_StatusLabel flightstatus;
}VPS_FlightLeg;

#define VPS_MAX_SEARCHFLIGHTLEGS 8

typedef struct  VPS_Flight_Status
{
   VPS_FlightStatusRequest flight;
   VPS_Count legscount;
   VPS_FlightLeg FlightLegs[VPS_MAX_SEARCHFLIGHTLEGS];     // lots of legs
}VPS_FlightStatus;


/* this is used in the VPS_TripParameter structure
 */
  
typedef struct VPS_When_Selection
{              
    VPS_TimeSelect bestwhen;           /* allows depart before 9:00, arrive before 7:00 */
    VPS_DateInfo date_when;
    VPS_TimeOfDay time_when;                     
}VPS_WhenSelection; 

/* this is the structure used to for one way and round trip requests
 */

typedef struct VPS_Trip_Parameter 
{                                
    char cFlightDepartsFrom[VPS_AirportLocationLength];
    char cFlightArrivesAt[VPS_AirportLocationLength];
    VPS_WhenSelection leave_return[2];        /* the second part of this is for the round trip request*/
}VPS_TripParameter;

/* the search results are returned using the following
 */

typedef struct VPS_Carrier_Leg
{
  char cCarrier[VPS_AirLineNameLength];
  char cFlightNumber[VPS_FlightNumberStringLength];
  char cConnectionLocation[VPS_AirportLocationLength];
}VPS_CarrierLeg;

/* one result
 */

#define VPS_MAX_FLIGHTAVAILABLELEGS 5

typedef struct VPS_Available_Flight
{
    VPS_RequestKey PickMe;      // return this to choose     
    VPS_DateInfo  departure_date;                
    VPS_TimeOfDay departure_time;
    VPS_TimeOfDay flightduration;
    VPS_TimeOfDay flightarrives;            // local time of arrival only
    char cFlightDepartsFrom[VPS_AirportLocationLength];
    char cFlightArrivesAt[VPS_AirportLocationLength];
    VPS_FlightFlags flags;
    VPS_Count legscount;
    VPS_CarrierLeg legs[VPS_MAX_FLIGHTAVAILABLELEGS];                       
}VPS_AvailableFlight;

/* all the results
 */

#define VPS_MAX_AVAILABLEAFTER  20
#define VPS_MAX_AVAILABLEBEFORE 20

typedef struct VPS_Available_Flights
{
    char cFlightDepartsFrom[VPS_AirportLocationLength];
    char cFlightArrivesAt[VPS_AirportLocationLength];
    VPS_Count beforecount;
    VPS_AvailableFlight flights_after[VPS_MAX_AVAILABLEAFTER ];
    VPS_Count aftercount;
    VPS_AvailableFlight flights_before[VPS_MAX_AVAILABLEBEFORE];
}VPS_AvailableFlights;

/* note that the VPS_TripParameter structure can be used for one way and 
 *
 * round trip search
 */

#define VPS_MAX_FLIGHTCHOOSELEGS 5

typedef struct VPS_Flight_Choice
{
    VPS_USFunds cost;
    VPS_RequestKey FinalChoice;      /* return this to choose     */
    VPS_DateInfo  departure_day[2];                     
    VPS_TimeOfDay departure_hour[2];
    VPS_TimeOfDay flightduration[2];
    VPS_TimeOfDay flightarrives[2];                 /* local time of arrival only */
    char cFlightDepartsFrom[2][VPS_AirportLocationLength];
    char cFlightArrivesAt[2][VPS_AirportLocationLength];
    VPS_FlightFlags flags[2];
    VPS_Count legscount[2];
    VPS_CarrierLeg legs[2][VPS_MAX_FLIGHTCHOOSELEGS];                        
}VPS_FlightChoice;

/* all the results
 */

#define VPS_MAX_PRICEDCHOOSE 10

typedef struct VPS_Priced_Flights
{
    char cFlightDepartsFrom[VPS_AirportLocationLength];
    char cFlightArrivesAt[VPS_AirportLocationLength];
    VPS_Count choicecount;
    VPS_FlightChoice flights_selected[VPS_MAX_PRICEDCHOOSE];
}VPS_PricedFlights;


typedef struct VPS_Card_Information
{
   char cCardTypes[VPS_DescriptionStringLength];
   VPS_RequestKey ToChooseCard;
}VPS_CardInformation;

typedef struct VPS_Out_Of_Policy_Reasons
{
  char cOutOfPolicyReason[VPS_DescriptionStringLength]; 
  VPS_RequestKey ToChooseReason;
}VPS_OutOfPolicyReasons;

#define VPS_MAX_CARDTYPES 10
#define VPS_MAX_POLICYREASONS 10
#define VPS_MAX_CHOICEDETAILLEGS 5
#define VPS_MAX_DETAILRESTRICTIONS 8

typedef struct VPS_Choice_Details
{
    VPS_RequestKey ToMakeReservation;
    VPS_USFunds basefare;
    VPS_USFunds taxes;  
    VPS_USFunds totalcost;  
    short totalmiles;
    VPS_TimeOfDay departure_time[2];
    VPS_DateInfo  departure_date[2];
    VPS_TimeOfDay TotalTimeInAir[2];
    VPS_TimeOfDay TotalTimeOnGround[2];     
    char * cTotalFlightTime[2];
    VPS_Count legscount[2];
    VPS_CarrierLeg Legs[2][VPS_MAX_CHOICEDETAILLEGS];
    VPS_Count restrictionscount;
    char cRestrictions[VPS_MAX_DETAILRESTRICTIONS][VPS_DescriptionStringLength]; 
    VPS_Count cardscount;
    VPS_CardInformation CardTypes[VPS_MAX_CARDTYPES];
    VPS_Count reasonscount;
    VPS_OutOfPolicyReasons Reasons[VPS_MAX_POLICYREASONS];
}VPS_ChoiceDetails;

/* final reservation information each 'key' is copied from
 * the apropriat spot in VPS_ChoiceDetails
 */

typedef struct VPS_Reservation_Information
{  
   VPS_RequestKey ToMakeReservation; 
   VPS_RequestKey ToChooseCard;
   VPS_RequestKey ToChooseReason;
}VPS_ReservationInformation;


/* function prototypes 
 */

/* Function name	: vps_Initialize
 * Description	    : 
 * Return type		: VPS_Status
 * Argument         : none
 */ 
VPS_Status vps_Initialize(void);

/* Function name	: vps_Connect
 * Description	    : 
 * Return type		: VPS_Status
 * Argument         : VPS_Handle*
 */ 
VPS_Status vps_Connect(VPS_Handle* hh);

/* Function name	: vps_Disconnect
 * Description	    : 
 * Return type		:  VPS_Status
 * Argument         :
 */ 
VPS_Status vps_Disconnect(VPS_Handle hh);

/* Function name	: vps_Terminate
 * Description	    : 
 * Return type		: VPS_Status
 * Argument         :
 */ 
void vps_Terminate(void);

/* Function name	: vps_AsynWait
 * Description	    : 
 * Return type		: VPS_Status
 * Argument         :
 */ 
int vps_AsynWait(VPS_Handle hh, VPS_AsyncID id, long *msec, VPS_Status *stat);

/* Function name	: vps_AsynStat
 * Description	    : 
 * Return type		: int
 * Argument         :
 */ 
int vps_AsynStat(VPS_Handle hh, VPS_AsyncID id, VPS_Status *stat);

/* Function name	: vps_AsynCancel
 * Description	    : 
 * Return type		: int
 * Argument         :
 */ 
int vps_AsynCancel(VPS_Handle hh, VPS_AsyncID id);

/* Function name	: vps_Login
 * Description	    : 
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_Login(VPS_Handle handle, VPS_AsyncID* async, 
   VPS_LogonData * login);

/* Function name	: vps_GetListOfItinerarys
 * Description	    : Returns the user's list of existing itineraries
 * Return type		: VPS_Status
 * Argument         :
 */
VPS_Status vps_ChangePasscode(VPS_Handle hh, short oldcode, short newcode);

/* Function name	: vps_GetListOfItinerarys
 * Description	    : Returns the user's list of existing itineraries
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_GetListOfItinerarys(VPS_Handle hh, VPS_AsyncID* async, 
    VPS_ItineraryList * fillme);

/* Function name	: vps_GetItineraryDetails
 * Description	    : Fills the details of the reguested itinerary
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_GetItineraryDetails(VPS_Handle hh, VPS_AsyncID* async, 
      VPS_RequestKey* ViewIt, VPS_ItineraryDetails* details);

/* Function name	: vps_FlightInformation
 * Description	    : Used to request status of a flight
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_FlightInformation(VPS_Handle hh, VPS_AsyncID* async, 
     VPS_FlightStatusRequest * plookingfor, VPS_FlightStatus* pfound); 

/* Function name	: vps_OneWayFlightsList
 * Description	    : Sets the desired flight paramaters and 
 *                    fills the one way flight choices
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_OneWayFlightsList(VPS_Handle hh, VPS_AsyncID* async, 
     VPS_TripParameter * pFlight, VPS_AvailableFlights *available);

/* Function name	: vps_OneWayChooseFlight
 * Description	    : Sets the choice of flight and fills the priced flights structure 
 *                    with the choice and alternatives.
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_OneWayChooseFlight(VPS_Handle hh, VPS_AsyncID* async, 
     VPS_RequestKey* pFinalChoice, VPS_PricedFlights * chosefrom);

/* Function name	: vps_OneWayTripConfimation
 * Description	    : Sets the priced choice and fills a flight details structure
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_OneWayTripConfimation(VPS_Handle hh, VPS_AsyncID* async, 
     VPS_RequestKey *pFinalChoice, VPS_ChoiceDetails *details);

/* Function name	: OneWayReservation
 * Description	    : Makes the reservation and fills an itinerary details structure
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status OneWayReservation(VPS_Handle hh, VPS_AsyncID* async, 
    VPS_ReservationInformation* preserve_with, VPS_ItineraryDetails* details);

/* Function name	: vps_RoundTripyFlightsList
 * Description	    : Sets the desired flights paramaters and 
 *                    fills the outbound flight choices
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_RoundTripFlightsList(VPS_Handle hh, VPS_AsyncID* async, 
     VPS_TripParameter * pFlight, VPS_AvailableFlights * poutbound);

/* Function name	: vps_RoundTripyReturnList
 * Description	    : Sets the outbouund flight choice and fills the returning 
 *                    flight choices
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_RoundTripyReturnList(VPS_Handle hh, VPS_AsyncID* async, 
     VPS_RequestKey *poutboundchoice, VPS_AvailableFlights * preturning);

/* Function name	: vps_RoundTripFinalChoices
 * Description	    : Sets the returning choice and fills the priced alternatives structure
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_RoundTripFinalChoices(VPS_Handle hh, VPS_AsyncID* async, 
      VPS_RequestKey *pchosenreturn, VPS_PricedFlights* ppriced);

// This provides the details

/* Function name	: vps_RoundTripConfimation
 * Description	    : Sets the priced choice and fills the details structure
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_RoundTripConfimation(VPS_Handle hh, VPS_AsyncID* async, 
      VPS_RequestKey *pFinalChoice, VPS_ChoiceDetails * pdetails); 


/* Function name	: vps_RoundTripReservation
 * Description	    : Used to make a reservation and view resulting itinerary details
                      The VPS_ChoiceDetails from vps_RoundTripConfimation 
                      provide the RequestKey elements used to make a reservation 
 * Return type		: VPS_Status
 * Argument         :
 */ 
VPS_Status vps_RoundTripReservation(VPS_Handle hh, VPS_AsyncID* async, 
   VPS_ReservationInformation* preserve_with, VPS_ItineraryDetails* details);

/* end of function prototypes 
 */

#endif