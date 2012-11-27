Attribute VB_Name = "Módulo1"
Const PI = 3.14159265358979

Sub Phi()
    Const ActualCol = 47
    Dim i As Integer
    Dim tSunset As Double
    Dim declination As Double
    Dim phiMeasure As Double
    Dim actualRow As Integer
    Dim bestVal As Double
    
    Cells(1, ActualCol).Value = "Phi"
    
    For actualRow = Cells(28, 1) To Cells(28, 2) Step 1  ' At row 28, Column 1 and 2 you should write
                                                         ' the initial and final position of reading values
        declination = Cells(actualRow, 41)
        tSunset = Cells(actualRow, 39)
        phiMeasure = CalculatePhi(declination, tSunset, bestVal)
        Cells(actualRow, ActualCol).Value = phiMeasure
        Cells(actualRow, ActualCol + 1).Value = bestVal
   Next actualRow
        
   
End Sub


Function CalculatePhi(declination As Double, tSunset As Double, bestVal) As Double
    Dim bestValue As Double
    Dim bestValueAux As Double
    Dim i As Double
    Dim iAux As Double
    
    tSunset = Math.Cos(tSunset)
    bestValue = ((Sin(-0.83 * PI / 180) - (Sin(-90 * PI / 180) * Sin(declination))) / (Cos(-90) * Cos(declination))) - tSunset
    bestVal = -90
    
    For i = -89 To 90 Step 0.01
        bestValueAux = ((Sin(-0.83 * PI / 180) - (Sin(i * PI / 180) * Sin(declination))) / Cos(i * PI / 180) * Cos(declination))
        bestValueAux = bestValueAux - tSunset
        If (Abs(bestValueAux) < Abs(bestValue)) Then
            bestValue = bestValueAux
            bestVal = i
        End If
        
    Next i
    
    CalculatePhi = bestValue
End Function