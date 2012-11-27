Attribute VB_Name = "Módulo1"
Sub EQDelete()
    Dim lastRow As Integer
    Dim initRow As Integer
    Dim rowsDeleted As Integer
    initRow = 0
    
    initRow = ActiveCell.Offset(2, 1).Row 'Return the number of second visible cell
    lastRow = LastRowInOneColumn()
    rowsDeleted = DeleteRows(initRow, lastRow)
    MsgBox rowsDeleted
End Sub

Function DeleteRows(initRow As Integer, lastRow As Integer)
    Dim count As Integer
    
    Application.ScreenUpdating = False
    count = 0
    For i = lastRow To initRow Step -1
       
        If (Cells(i, 3).Value <= "82" And Cells(i, 3).Value >= "79") Or (Cells(i, 3).Value <= "268" And Cells(i, 3).Value >= "265") Then
            Rows(i).Delete
            count = count + 1
        End If
    Next i
        
    Application.ScreenUpdating = True
    DeleteRows = count
End Function

Function LastRowInOneColumn() As Integer
'Find the last used row in a Column: column A in this example
    Dim lastRow As Long
    With ActiveSheet
        lastRow = .Cells(.Rows.count, "A").End(xlUp).Row
    End With
    LastRowInOneColumn = lastRow
End Function

