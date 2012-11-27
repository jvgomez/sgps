%This function returns the date (day and month) for a day given from 365
%(or 366).
%
% [day, month] = getDayMonth(day)

%  Part of the SGPS Project. http://www.sgpsproject.org
%  Copyright (C) 2012 Javier V. Gómez
%
%  This program is free software: you can redistribute it and/or modify
%  it under the terms of the GNU General Public License as published by
%  the Free Software Foundation, either version 3 of the License, or
%  (at your option) any later version.
%  This program is distributed in the hope that it will be useful,
%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%  GNU General Public License for more details.
%  You should have received a copy of the GNU General Public License
%  along with this program.  If not, see <http://www.gnu.org/licenses/>.

function [day, month] = getDayMonth(measureDay)

if (measureDay <= 31)
		day = measureDay;
		month = 1;	
end
if ((measureDay >= 32)  &&	(measureDay <= 59))  
		day = measureDay - 31;
		month = 2;
end
if ((measureDay >= 60)  &&	(measureDay <= 90))  
		day = measureDay - 59;
		month = 3;
end
if ((measureDay >= 91)  &&	(measureDay <= 120)) 
		day = measureDay - 90;
		month = 4;
end
if ((measureDay >= 121) &&	(measureDay <= 151)) 
		day = measureDay - 120;
		month = 5;
end
if ((measureDay >= 152) &&	(measureDay <= 181)) 
		day = measureDay - 151;
		month = 6;
end
if ((measureDay >= 182) &&	(measureDay <= 212)) 
		day = measureDay - 181;
		month = 7;
end
if ((measureDay >= 213) &&	(measureDay <= 243)) 
		day = measureDay - 212;
		month = 8;
end
if ((measureDay >= 244) &&	(measureDay <= 273)) 
		day = measureDay - 243;
		month = 9;
end
if ((measureDay >= 274) &&	(measureDay <= 304)) 
		day = measureDay - 273;
		month = 10;
end
if ((measureDay >= 305) &&	(measureDay <= 334)) 
		day = measureDay - 304;
		month = 11;
end
if ((measureDay >= 335) &&	(measureDay <= 365)) 
		day = measureDay - 334;
		month = 12;
end
if (measureDay == 366)
		day = 31;
		month = 12;
end


