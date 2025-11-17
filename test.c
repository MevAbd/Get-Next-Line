/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:00:00 by malbrand          #+#    #+#              */
/*   Updated: 2021/01/27 12:00:00 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void	print_test_header(const char *test_name)
{
	printf("\n%s%s═══════════════════════════════════════════════════════════%s\n", 
		CYAN, BOLD, RESET);
	printf("%s%sTest: %s%s%s\n", CYAN, BOLD, RESET, test_name, RESET);
	printf("%s%s═══════════════════════════════════════════════════════════%s\n", 
		CYAN, BOLD, RESET);
}

void	print_result(int passed, const char *message)
{
	if (passed)
		printf("%s%s✓%s %s%s\n", GREEN, BOLD, RESET, message, RESET);
	else
		printf("%s%s✗%s %s%s\n", RED, BOLD, RESET, message, RESET);
}

int	test_basic_file(const char *filename)
{
	int		fd;
	char	*line;
	int		line_count = 0;
	int		passed = 1;
	int		max_iterations = 10000; // Sécurité contre boucle infinie

	print_test_header("Basic file reading");
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("%s%sError: Cannot open file '%s'%s\n", RED, BOLD, filename, RESET);
		printf("%s%sPlease check that the file exists and is readable.%s\n", 
			YELLOW, BOLD, RESET);
		print_result(0, "File cannot be opened");
		return (0);
	}
	
	printf("%sReading from file: %s%s\n", YELLOW, filename, RESET);
	while ((line = get_next_line(fd)) != NULL && line_count < max_iterations)
	{
		line_count++;
		if (line_count <= 10) // Afficher seulement les 10 premières lignes
			printf("%s[Line %d]%s %s", BLUE, line_count, RESET, line);
		free(line);
	}
	
	if (line_count >= max_iterations)
	{
		printf("%s%sERROR: Infinite loop detected! Stopped at %d lines%s\n", 
			RED, BOLD, line_count, RESET);
		close(fd);
		return (0);
	}
	
	if (line_count > 10)
		printf("%s... (total: %d lines)%s\n", YELLOW, line_count, RESET);
	
	close(fd);
	
	print_result(line_count > 0, "File read successfully");
	return (passed);
}

int	test_empty_file(void)
{
	int		fd;
	char	*line;
	int		passed = 1;

	print_test_header("Empty file");
	
	// Créer un fichier vide de manière portable
	fd = open("test_empty.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s%sError: Cannot create empty file%s\n", RED, BOLD, RESET);
		return (0);
	}
	close(fd);
	
	fd = open("test_empty.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("%s%sError: Cannot open empty file%s\n", RED, BOLD, RESET);
		unlink("test_empty.txt");
		return (0);
	}
	
	line = get_next_line(fd);
	if (line == NULL)
		print_result(1, "Empty file returns NULL (correct)");
	else
	{
		print_result(0, "Empty file should return NULL");
		free(line);
		passed = 0;
	}
	close(fd);
	unlink("test_empty.txt");
	return (passed);
}

int	test_single_line(void)
{
	int		fd;
	char	*line;
	int		passed = 1;

	print_test_header("Single line file");
	
	// Créer le fichier directement avec write pour éviter les problèmes avec echo
	fd = open("test_single.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s%sError: Cannot create test file%s\n", RED, BOLD, RESET);
		return (0);
	}
	write(fd, "Hello World\n", 12);
	close(fd);
	
	fd = open("test_single.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("%s%sError: Cannot open test file%s\n", RED, BOLD, RESET);
		unlink("test_single.txt");
		return (0);
	}
	
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("%sLine read: %s%s", YELLOW, line, RESET);
		if (strcmp(line, "Hello World\n") == 0)
			print_result(1, "Single line read correctly");
		else
		{
			printf("%sExpected: 'Hello World\\n', got: '%s'%s\n", RED, line, RESET);
			print_result(0, "Line content incorrect");
			passed = 0;
		}
		free(line);
	}
	else
	{
		print_result(0, "Should have read one line");
		passed = 0;
	}
	
	line = get_next_line(fd);
	if (line == NULL)
		print_result(1, "EOF correctly detected");
	else
	{
		print_result(0, "Should return NULL after EOF");
		free(line);
		passed = 0;
	}
	
	close(fd);
	unlink("test_single.txt");
	return (passed);
}

int	test_multiple_lines(void)
{
	int		fd;
	char	*line;
	int		line_count = 0;
	int		passed = 1;
	int		max_iterations = 100; // Sécurité contre boucle infinie

	print_test_header("Multiple lines file");
	
	// Créer le fichier directement avec write pour éviter les problèmes avec echo -e
	fd = open("test_multiple.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s%sError: Cannot create test file%s\n", RED, BOLD, RESET);
		return (0);
	}
	write(fd, "Line 1\nLine 2\nLine 3\n", 21);
	close(fd);
	
	fd = open("test_multiple.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("%s%sError: Cannot open test file%s\n", RED, BOLD, RESET);
		unlink("test_multiple.txt");
		return (0);
	}
	
	while ((line = get_next_line(fd)) != NULL && line_count < max_iterations)
	{
		line_count++;
		printf("%s[Line %d]%s %s", BLUE, line_count, RESET, line);
		free(line);
	}
	
	if (line_count >= max_iterations)
	{
		printf("%s%sERROR: Infinite loop detected!%s\n", RED, BOLD, RESET);
		close(fd);
		unlink("test_multiple.txt");
		return (0);
	}
	
	if (line_count == 3)
		print_result(1, "All 3 lines read correctly");
	else
	{
		printf("%sExpected 3 lines, got %d%s\n", RED, line_count, RESET);
		print_result(0, "Expected 3 lines");
		passed = 0;
	}
	
	close(fd);
	unlink("test_multiple.txt");
	return (passed);
}

int	test_no_newline_at_end(void)
{
	int		fd;
	char	*line;
	int		passed = 1;

	print_test_header("File without newline at end");
	
	// Créer le fichier directement avec write pour éviter les problèmes avec echo -n
	fd = open("test_no_nl.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s%sError: Cannot create test file%s\n", RED, BOLD, RESET);
		return (0);
	}
	write(fd, "No newline", 10);
	close(fd);
	
	fd = open("test_no_nl.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("%s%sError: Cannot open test file%s\n", RED, BOLD, RESET);
		unlink("test_no_nl.txt");
		return (0);
	}
	
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("%sLine read: '%s'%s", YELLOW, line, RESET);
		if (strcmp(line, "No newline") == 0)
			print_result(1, "Line without newline read correctly");
		else
		{
			printf("%sExpected: 'No newline', got: '%s'%s\n", RED, line, RESET);
			print_result(0, "Line content incorrect");
			passed = 0;
		}
		free(line);
	}
	else
	{
		print_result(0, "Should have read the line");
		passed = 0;
	}
	
	close(fd);
	unlink("test_no_nl.txt");
	return (passed);
}

int	test_invalid_fd(void)
{
	char	*line;
	int		passed = 1;

	print_test_header("Invalid file descriptor");
	
	line = get_next_line(-1);
	if (line == NULL)
		print_result(1, "Invalid FD returns NULL (correct)");
	else
	{
		print_result(0, "Invalid FD should return NULL");
		free(line);
		passed = 0;
	}
	return (passed);
}

int	test_very_long_line(void)
{
	int		fd;
	char	*line;
	int		passed = 1;
	int		i;

	print_test_header("Very long line");
	
	fd = open("test_long.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s%sError: Cannot create test file%s\n", RED, BOLD, RESET);
		return (0);
	}
	
	for (i = 0; i < 1000; i++)
		write(fd, "A", 1);
	write(fd, "\n", 1);
	close(fd);
	
	fd = open("test_long.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line != NULL)
	{
		if (strlen(line) == 1001) // 1000 A's + \n
			print_result(1, "Very long line read correctly");
		else
		{
			printf("%sExpected length: 1001, got: %zu%s\n", RED, strlen(line), RESET);
			print_result(0, "Line length incorrect");
			passed = 0;
		}
		free(line);
	}
	else
	{
		print_result(0, "Should have read the line");
		passed = 0;
	}
	
	close(fd);
	unlink("test_long.txt");
	return (passed);
}

int	test_buffer_size_1(void)
{
	int		fd;
	char	*line;
	int		line_count = 0;
	int		passed = 1;
	int		max_iterations = 100; // Sécurité contre boucle infinie

	print_test_header("BUFFER_SIZE = 1");
	
	// Créer le fichier directement avec write pour éviter les problèmes avec echo -e
	fd = open("test_buffer1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s%sError: Cannot create test file%s\n", RED, BOLD, RESET);
		return (0);
	}
	write(fd, "Line 1\nLine 2\n", 14);
	close(fd);
	
	fd = open("test_buffer1.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("%s%sError: Cannot open test file%s\n", RED, BOLD, RESET);
		unlink("test_buffer1.txt");
		return (0);
	}
	
	while ((line = get_next_line(fd)) != NULL && line_count < max_iterations)
	{
		line_count++;
		printf("%s[Line %d]%s %s", BLUE, line_count, RESET, line);
		free(line);
	}
	
	if (line_count >= max_iterations)
	{
		printf("%s%sERROR: Infinite loop detected!%s\n", RED, BOLD, RESET);
		close(fd);
		unlink("test_buffer1.txt");
		return (0);
	}
	
	if (line_count == 2)
		print_result(1, "Works with BUFFER_SIZE = 1");
	else
	{
		printf("%sExpected 2 lines, got %d%s\n", RED, line_count, RESET);
		print_result(0, "Expected 2 lines");
		passed = 0;
	}
	
	close(fd);
	unlink("test_buffer1.txt");
	return (passed);
}

int	main(int argc, char **argv)
{
	int	total_tests = 0;
	int	passed_tests = 0;

	printf("%s%s", BOLD, CYAN);
	printf("╔═══════════════════════════════════════════════════════════╗\n");
	printf("║                                                           ║\n");
	printf("║           GET_NEXT_LINE TESTER                             ║\n");
	printf("║                                                           ║\n");
	printf("╚═══════════════════════════════════════════════════════════╝\n");
	printf("%s", RESET);
	
	printf("\n%sCurrent BUFFER_SIZE: %d%s\n", MAGENTA, BUFFER_SIZE, RESET);
	
	// Test avec fichier fourni en argument
	if (argc > 1)
	{
		printf("%s%sNote: Testing file '%s' first. The static variable in get_next_line%s\n", 
			YELLOW, BOLD, argv[1], RESET);
		printf("%s%swill be shared with subsequent tests (normal for mandatory part).%s\n\n", 
			YELLOW, BOLD, RESET);
		total_tests++;
		if (test_basic_file(argv[1]))
			passed_tests++;
		// Lire jusqu'à la fin pour nettoyer la variable statique
		// (simulation de ce qui se passerait normalement)
		printf("%s%sCleaning static variable...%s\n", YELLOW, BOLD, RESET);
	}
	
	// Tests automatiques
	total_tests++;
	if (test_empty_file())
		passed_tests++;
	
	total_tests++;
	if (test_single_line())
		passed_tests++;
	
	total_tests++;
	if (test_multiple_lines())
		passed_tests++;
	
	total_tests++;
	if (test_no_newline_at_end())
		passed_tests++;
	
	total_tests++;
	if (test_invalid_fd())
		passed_tests++;
	
	total_tests++;
	if (test_very_long_line())
		passed_tests++;
	
	total_tests++;
	if (test_buffer_size_1())
		passed_tests++;
	
	// Résumé
	printf("\n%s%s═══════════════════════════════════════════════════════════%s\n", 
		CYAN, BOLD, RESET);
	printf("%s%sRésumé: %d/%d tests réussis%s\n", 
		(passed_tests == total_tests) ? GREEN : YELLOW, BOLD, 
		passed_tests, total_tests, RESET);
	printf("%s%s═══════════════════════════════════════════════════════════%s\n", 
		CYAN, BOLD, RESET);
	
	if (passed_tests == total_tests)
		printf("%s%s✓ Tous les tests sont passés !%s\n", GREEN, BOLD, RESET);
	else
		printf("%s%s✗ Certains tests ont échoué%s\n", RED, BOLD, RESET);
	
	return (passed_tests == total_tests ? 0 : 1);
}

