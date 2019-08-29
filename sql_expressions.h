#pragma once

#include <QString>

struct SQLQueries
{
private:
	const QString tableName = "TestInfo";
	int year, month, day;

public:	
	QString selectionByDate	= ("SELECT StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress"
		" FROM TestInfo "
		" WHERE(	DATEPART(yy, StartDateTime) =  %1 "
		" AND		DATEPART(mm, StartDateTime) = %2 "
		" AND		DATEPART(dd, StartDateTime) = %3)");

	QString selectionRangeDate = ("SELECT StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress"
		" FROM TestInfo "
		" WHERE(	DATEPART(yy, StartDateTime) between  %1 and %2 "
		" AND		DATEPART(mm, StartDateTime) between  %3 and %4"
		" AND		DATEPART(dd, StartDateTime) between  %5 and %6)");

};