Attribute VB_Name = "Módulo1"
Const MIN = -50
Const MAX = 50
Const INTERVAL = 10
Const INIT_ROW = 2
Const LAST_ROW = 366
Const COORD_COLUMN = 2
Const LAT_ROW = 3
Const LON_ROW = 4
Const ERROR_LON_COLUMN = 38
Const DATE_COLUMN = 4
Const DATE_INIT_ROW = 2
Const DATE_LAST_ROW = 366
Const YEAR = 1995


Sub ErrorLonAverage()
    On Error Resume Next
    Dim numberSheet As Integer
    Dim dataSheet As Integer
    Dim lat As Double
    Dim lon As Double
    Dim i As Integer
    Dim readColumns As Integer
    Dim color As Byte
    Dim RowRange As Range
    Dim yesNo As VbMsgBoxResult
    Dim dateAux As Date
    Dim auxDate As Integer
    
    For i = 1 To Sheets.Count
        If (Sheets(i).Name = "ErrorLon") Then
            yesNo = MsgBox("If you continue, will erase all data on ErrorLon. Do you want to continue?", vbYesNo, "¿Continue?")
            If (yesNo = vbYes) Then
                Sheets(i).Delete
                i = Sheets.Count + 1
            End If
        End If
    Next i
    
    Sheets.Add
    ActiveSheet.Name = "ErrorLon"
    numberSheet = ActiveSheet.Index
    
    For i = 1 To Sheets.Count
        If (Sheets(i).Name = "Errors 2") Then
            dataSheet = i
            i = Sheets.Count + 1
        End If
    Next i
    dateAux = CDate("01/01/" & YEAR)
    auxDate = 0
    
    For i = DATE_INIT_ROW To DATE_LAST_ROW Step 1
        Sheets(dataSheet).Cells(i, DATE_COLUMN).Value = dateAux + auxDate
        Sheets(numberSheet).Cells(auxDate + 3, 1).Value = dateAux + auxDate
        auxDate = auxDate + 1
   Next i
        readColumns = 2 'First Column have a date of day about the error, so this value should be start at 2
        color = 3
        color = 3 Mod color

        For lat = MIN To MAX Step INTERVAL
            Sheets(dataSheet).Cells(LAT_ROW, COORD_COLUMN).Value = lat

            For lon = MIN To MAX Step INTERVAL

                Sheets(dataSheet).Cells(LON_ROW, COORD_COLUMN).Value = lon
                Sheets(numberSheet).Cells(1, readColumns).Value = "Lon = " & lon & " Lat = " & lat
                Sheets(numberSheet).Cells(2, readColumns).Value = "Error Longitude"

                If color = 0 Then
                    Sheets(numberSheet).Cells(1, readColumns).Interior.ColorIndex = 36
                    Sheets(numberSheet).Cells(2, readColumns).Interior.ColorIndex = 36
                Else
                    Sheets(numberSheet).Cells(1, readColumns).Interior.ColorIndex = 17
                    Sheets(numberSheet).Cells(2, readColumns).Interior.ColorIndex = 17
                End If

                For i = INIT_ROW To LAST_ROW Step 1
                    Sheets(numberSheet).Cells((i - INIT_ROW) + 3, readColumns).Value = Sheets(dataSheet).Cells(i, ERROR_LON_COLUMN).Value

                    If color = 0 Then
                        Sheets(numberSheet).Cells((i - INIT_ROW) + 4, readColumns).Interior.ColorIndex = 19
                    Else
                        Sheets(numberSheet).Cells((i - INIT_ROW) + 5, readColumns).Interior.ColorIndex = 24
                    End If
                Next i

                readColumns = readColumns + 1
                color = color + 2
                color = 3 Mod color
            Next lon
        Next lat
        Sheets(numberSheet).Cells(2, readColumns).Value = "Average"
        Sheets(numberSheet).Cells(2, readColumns + 1).Value = "Max"
        Sheets(numberSheet).Cells(2, readColumns + 2).Value = "Min"


        For i = INIT_ROW + 1 To LAST_ROW + 1 Step 1

            Set RowRange = Range(Cells((i - INIT_ROW) + 2, 2), Cells((i - INIT_ROW) + 2, readColumns - 1))
            Sheets(numberSheet).Cells((i - INIT_ROW) + 2, readColumns).Value = Application.WorksheetFunction.Average(RowRange)
            Sheets(numberSheet).Cells((i - INIT_ROW) + 2, readColumns + 1).Value = Application.WorksheetFunction.MAX(RowRange)
            Sheets(numberSheet).Cells((i - INIT_ROW) + 2, readColumns + 2).Value = Application.WorksheetFunction.MIN(RowRange)
        Next i

End Sub
