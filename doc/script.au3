#include <ProgressConstants.au3>
#include <MsgBoxConstants.au3>
#include <WindowsConstants.au3>
#include <ButtonConstants.au3>
#include <StaticConstants.au3>
#include <GUIConstantsEx.au3>
#include <ColorConstants.au3>
#include <FontConstants.au3>


Local $a
Local $count = 0
Local $progress

Local $hMsgBoxCnt, $sLable
Local $iWidth = 200, $iHeight = 100
Local Const $sFont = "Comic Sans Ms"

HotKeySet("{ESC}", "Terminate")


While 1
	  ; Display the run time
	  $count = $count +1

	  $hMsgBoxCnt = GUICreate("COUNTER", $iWidth, 100, 100, 100, $WS_DLGFRAME, -1)
	  $sLable = GUICtrlCreateLabel($count, 0, 5, $iWidth, 40, $SS_CENTER)
	  GUICtrlSetFont($sLable, 28, $FW_NORMAL, $GUI_FONTNORMAL, $sFont)
	  GUICtrlSetColor($sLable, $COLOR_RED)
	  GUISetState(@SW_SHOW, $hMsgBoxCnt)

	  $prog = "C:\Workzone\UpdateFW_20191119\UpdateMcuApp.exe"
	  ;$prog = "C:\Users\jingtai_wu\Desktop\UpdateFW\UpdateFW_20191119\UpdateMcuApp.exe"
	  Run($prog)

	  Local $hWnd = WinWait("UpdateMcuApp 1.5 (NXP)", "", 10)
	  ControlClick($hWnd, "", "WindowsForms10.BUTTON.app.0.378734a2")

	  Local $hSubWnd = WinWait("Open Image File", "", 10)
	  If $a = 1 Then
		 $a = 2
		 ControlSetText($hSubWnd,"","Edit1","pdb_red.hex")
	  Else
		 $a = 1
		 ControlSetText($hSubWnd,"","Edit1","pdb_green.hex")
		 Endif

	  ControlClick($hSubWnd, "", "Button1")
	  ControlClick($hWnd, "", "WindowsForms10.BUTTON.app.0.378734a1")

	  Local $hControl = ControlGetHandle($hWnd, "", "WindowsForms10.STATIC.app.0.378734a10")

	  DO
		 $progress = ControlGetText($hWnd,"",$hControl)
	  Until $progress = 100


	  If $progress = 100 Then

		 $progress = 0

		 Local $iResult = MsgBox_CountDown("App Running", "Restarting process within", 12)
		 If $iResult = $IDOK Then
			 ConsoleWrite("@@ Debug(" & @ScriptLineNumber & ") : OK Pressed" & @CRLF)
		 ElseIf $iResult = $IDTIMEOUT Then
			 ConsoleWrite("@@ Debug(" & @ScriptLineNumber & ") : Timeout" & @CRLF)
		 Else
			 ConsoleWrite("@@ Debug(" & @ScriptLineNumber & ") : Cancel Pressed" & @CRLF)
		  EndIf

	  EndIf

	  WinClose($hSubWnd)
	  GUIDelete($hMsgBoxCnt)
	  WinClose($hWnd)
WEnd

; #FUNCTION# ================================================================================
; Name...........: MsgBox_CountDown
; Description ...: MsgBox with visual CountDown
; Syntax.........: MsgBox_CountDown($sTitle, $sMessage, $iTimeOut = 30, $hWnd = 0)
; Parameters ....: $sTitle - The title of the message box
;				   $sMessage - The text of the message box
;				   $iTimeOut - Optional - Timeout in seconds
;				   $hWnd - Optional - The window handle to use as the parent for this dialog.
; Return values .: Success - Following return codes:
;						OK : $IDOK (1)
;				   		Timeout : $IDTIMEOUT (-1)
;                  		Cancel : $IDCANCEL (2)
;                  Failure - Returns @Error:
;				   |1 - Erroneous Timout value, should be higher than 0
; Author ........: GreenCan
; Modified.......:
; Remarks .......: Not meant as a replacement of MsgBox
; Related .......:
; Link ..........:
; Example .......: No
; ===========================================================================================
Func MsgBox_CountDown($sTitle, $sMessage, $iTimeOut = 30, $hWnd = 0)
	If $iTimeOut < 0 Then Return SetError(1, 0, 0)

	Local $hMsgBoxCtDwn, $hButtonOK, $hButtonCancel, $Sec = @SEC, $sMsg, $iMsg
	Local $iWidth = 200, $iHeight = 100
    $hMsgBoxCtDwn = GUICreate($sTitle, $iWidth, 100, -1, -1, $WS_DLGFRAME, -1, $hWnd)
    $sMsg = GUICtrlCreateLabel($sMessage & " " & $iTimeOut & " sec", 0, 20, $iWidth, 28, $SS_CENTER)
	$hButtonOK = GUICtrlCreateButton("OK", ($iWidth/2) - 85, $iHeight - 50,  80, 20, BitOR($BS_CENTER, $BS_DEFPUSHBUTTON))
    $hButtonCancel = GUICtrlCreateButton("Cancel", ($iWidth/2) + 5, $iHeight - 50, 80, 20, $BS_CENTER)
    GUISetState(@SW_SHOW)

	While 1
		$iMsg = GUIGetMsg()
		Select
			Case $iMsg = $hButtonOK
				GUIDelete($hMsgBoxCtDwn)
				Return $IDOK

			Case $iMsg = $hButtonCancel Or $iMsg = $GUI_EVENT_CLOSE
				GUIDelete($hMsgBoxCtDwn)
				Return $IDCANCEL

			Case $iTimeOut = 0
				GUIDelete($hMsgBoxCtDwn)
				Return $IDTIMEOUT
		EndSelect

		If @SEC <> $Sec Then
			$Sec = @SEC
			$iTimeOut -= 1
			GUICtrlSetData($sMsg, $sMessage & " " & $iTimeOut & " sec")

        EndIf
	WEnd

EndFunc	;==>MsgBox_CountDown

Func Terminate()

   	WinClose($hSubWnd)
	GUIDelete($hMsgBoxCnt)
	WinClose($hWnd)
    Exit
EndFunc   ;==>Terminate

