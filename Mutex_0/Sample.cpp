/*
CriticalSection -> �������  :: �ڵ����� �����ذ�
mutex = Ŀ�θ�� :: �ü���� ������ �޴´�. 
				 :: ���μ����� �ߺ������� ���� 
				 :: ���������
HANDLE mutex; -> Critical_Section
mutex = InitializeCriticalSection -> CreateMutex(NULL, FALSE, "wstr"); :: �������̸���(wstr) ���ؽ��� �ϳ��� �����Ѵ�.
if(GetlastError() == ERROR_ALREADY_EXISTS) :: �̹� �������̸��� ���ؽ��� �����Ǿ��ִ�. :: ���μ����� 2������ɼ�����.
{
	CloseHandle(mutex)
}
CloseHandle -> deletecriticalSection
EnterCriticalSection -> waitforsingleobject(,INFINITE) :: ���ȣ���� 
													   :: ���ð��� ����(����)�Ҽ��ִ�.
Leave -> RleaseMutex :: ��ȣ����
WAIT_TIMEOUT
WAIT_OBJECT_0
*/
/*
	�������� :: ī���ͱ��(��ȣ���°��ɶ����� ī���� + 1)
			 :: release (ī���� - 1)
			 :: ī���͸�ŭ�� �����Ѵ�.
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Server Lib :: winsock2.h -> ��ܿ� ����
//	Critical_Section -> mutex
//	Recv, Send ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////