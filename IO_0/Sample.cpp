/*
	//���ϻ���
	HANDLE = CreateFile(�����̸�, GENERIC_WRITE,0,NULL,CREATE_ALWAYS(�����ǻ���), );
	WriteFile(); <- SOCKET�� ������ ��Ŷ�� �������ִ�
	CloseHandle();

	HANDLE = CreateFile();
	ReadFile();
	CloseHandle();
*/

/*
	-> �񵿱�
	HANDLE = CreateFile();
	WriteFile();
	CloseHandle();

	OverLapped -> ��ŭ�о�����Ȯ���Ҽ��ִ� ����ü  ::��������
*/
// GetFileSize -> ���� ������ �޾ƿ��� �Լ� :: API
// GetOverlappedResult(); :: ov��ȯ + ���ϻ����� , ���������ڰ� TRUE -> ���������� ��ȯ����.
//						  :: �߰���� ���� �������Ȯ��
//                        :: GetLastError() == ERROR_IO_PENDING -> ������
// OverLapped.internal~ �� �ü������. Event ���� �������۰���.
/* CreateFile(GENERIC_WRITE | GENERIC_READ) �а��� */
/* 
	Offset �������ϸ� ���ڿ����Ͷ� ��°����� :: Offset�� 1024�� 1024����Ʈ���� ������
	A File // B File
	100    -> 0   + 100       :: �񵿱� 1��
	100    -> 100 + 100		  :: �񵿱� 1��  { ��ü�� �񵿱� 1�� ���� }
	100    -> 200 + 100 ......:: �񵿱� 1��
	����       ��
*/
/* �񵿱� :: �Ϸ�Ǳ��������� �߰������� �˼�����. */
// ERROR_HANDLE_EOF ������ ��
// PENDING ���� ov�߰�üũ