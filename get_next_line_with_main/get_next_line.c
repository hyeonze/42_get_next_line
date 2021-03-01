/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 14:13:48 by hann              #+#    #+#             */
/*   Updated: 2020/09/01 21:08:53 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	backup_to_line(char **line,
	char **backup, char *is_newline)
{
	char	*tmp;

	if (is_newline != NULL) // 개행문자가 있을 경우
	{
		*line = ft_strndup(*backup, is_newline - *backup); // 'line'에 개행 전까지 저장
		tmp = ft_strndup(is_newline + 1, ft_strlen(is_newline + 1)); // 'tmp'에 개행 후 저장
		free(*backup); // 'backup'해제
		*backup = tmp; // 개행 후 남은 내용 저장
		return (SUCCESS); // 'SUCCESS'(=1) 반환
	}
	if (*backup != NULL) // 'backup'에 개행은 없지만 내용이 있을 경우(파일의 끝)
	{
		*line = *backup; // 'line'에 남은 부분 저장
		*backup = NULL; // 'backup'는 비운다
	}
	else // 'backup'이 빈 파일을 읽었을 경우
		*line = ft_strndup("", 1); // 빈 문자열을 넣는다
	return (EOF); // 'EOF'(=0)반환
}

int			get_next_line(int fd, char **line)
// fd : 읽기용 파일 디스크립터
// line : 읽은 것의 값이 들어갈 곳
{
	static char	*backup[MAX_FD]; // read한 버퍼를 백업할 static버퍼
	char		buff[BUFFER_SIZE + 1]; // 파일을 read할 임시 버퍼
	int			byte; // 읽은 바이트수 저장할 변수
	char		*tmp;
	char		*is_newline; // '\n'의 위치 저장할 포인터 변수

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0) // 에러처리(fd가 음수, 읽을게 없음, 버퍼사이즈가 0이하)
		return (ERROR); // ERROR(=-1) 리턴
	while ((is_newline = ft_strchr(backup[fd], '\n')) == 0
			&& (byte = read(fd, buff, BUFFER_SIZE)) > 0)
	// is_newline에 '\n'이 위치한 포인터주소 저장
	// 'BUFFER_SIZE'만큼 'fd'를 읽어 'buff'에 저장. 'byte'에는 읽은 바이트수가 저장됨. 실패시 -1반환. 끝까지 읽은경우 0반환.
	// (read를 호출하게 되면 버퍼만큼 라인을 읽게됨, buf를 정적변수 backup에 백업한다.)
	// backup[fd]에서 '\n'이 발견되지 않고, read에 성공했을 경우만 반복문 진입
	{
		buff[byte] = 0; // buff의 마지막자리에 NULL저장
		tmp = (backup[fd] == NULL) ?
			ft_strndup(buff, byte) : ft_strjoin(backup[fd], buff);
		// backup[fd]가 NULL일 경우 tmp에 'buff'의 문자 'byte'개만큼 저장
		// backup[fd]가 NULL이 아닐 경우 tmp에 'backup[fd] + buff' 저장
		if (backup[fd] != 0)
			free(backup[fd]); // 'backup[fd]'가 NULL이 아닐 경우 free
		backup[fd] = tmp; // 'backup[fd]'에 backup저장
	}
	if (byte < 0)
		return (ERROR); // byte가 음수일 경우 ERROR(-1) 리턴
	return (backup_to_line(line, &backup[fd], is_newline));
}
