/*
CriticalSection -> 유저모드  :: 코딩으로 전부해결
mutex = 커널모드 :: 운영체제의 관리를 받는다. 
				 :: 프로세스의 중복실행을 막음 
				 :: 데드락방지
HANDLE mutex; -> Critical_Section
mutex = InitializeCriticalSection -> CreateMutex(NULL, FALSE, "wstr"); :: 동일한이름의(wstr) 뮤텍스는 하나만 생성한다.
if(GetlastError() == ERROR_ALREADY_EXISTS) :: 이미 동일한이름의 뮤텍스가 생성되어있다. :: 프로세스가 2번실행될수없다.
{
	CloseHandle(mutex)
}
CloseHandle -> deletecriticalSection
EnterCriticalSection -> waitforsingleobject(,INFINITE) :: 비신호상태 
													   :: 대기시간을 지정(제어)할수있다.
Leave -> RleaseMutex :: 신호상태
WAIT_TIMEOUT
WAIT_OBJECT_0
*/
/*
	세마포어 :: 카운터기능(신호상태가될때마다 카운터 + 1)
			 :: release (카운터 - 1)
			 :: 카운터만큼만 실행한다.
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Server Lib :: winsock2.h -> 상단에 선언
//	Critical_Section -> mutex
//	Recv, Send 나누기
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////