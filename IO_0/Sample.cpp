/*
	//파일생성
	HANDLE = CreateFile(파일이름, GENERIC_WRITE,0,NULL,CREATE_ALWAYS(무조건생성), );
	WriteFile(); <- SOCKET을 넣으면 패킷을 보낼수있다
	CloseHandle();

	HANDLE = CreateFile();
	ReadFile();
	CloseHandle();
*/

/*
	-> 비동기
	HANDLE = CreateFile();
	WriteFile();
	CloseHandle();

	OverLapped -> 얼만큼읽었는지확인할수있는 구조체  ::같은놈사용
*/
// GetFileSize -> 파일 사이즈 받아오는 함수 :: API
// GetOverlappedResult(); :: ov반환 + 파일사이즈 , 마지막인자값 TRUE -> 끝날때까지 반환안함.
//						  :: 중간결과 ㄴㄴ 최종결과확인
//                        :: GetLastError() == ERROR_IO_PENDING -> 진행중
// OverLapped.internal~ 은 운영체제관리. Event 등은 직접조작가능.
/* CreateFile(GENERIC_WRITE | GENERIC_READ) 읽고쓰기 */
/* 
	Offset 값설정하면 값뒤에부터또 출력가능함 :: Offset이 1024면 1024바이트부터 시작함
	A File // B File
	100    -> 0   + 100       :: 비동기 1개
	100    -> 100 + 100		  :: 비동기 1개  { 전체가 비동기 1개 ㄴㄴ }
	100    -> 200 + 100 ......:: 비동기 1개
	읽음       씀
*/
/* 비동기 :: 완료되기전까지는 중간과정을 알수없다. */
// ERROR_HANDLE_EOF 파일의 끝
// PENDING 에는 ov중간체크