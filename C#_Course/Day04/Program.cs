using System.Diagnostics;
using Day04;
using static Day04.Book;

internal class Program
{
    private static void Main(string[] args)
    {
        List<Book> books = new List<Book>();

        string[] book1Authors = { "J. K. Rowling" };
        books.Add(new Book("978-0-7475-3269-9", "Harry Potter and the Philosopher's Stone",
            book1Authors, new DateTime(1997, 6, 26), 39.99m));

        string[] book2Authors = { "J. R. R. Tolkien" };
        books.Add(new Book("978-0-0071-3659-9", "The Lord of the Rings: The Fellowship of the Ring",
            book2Authors, new DateTime(1954, 7, 29), 12.29m));

        string[] book3Authors = { "Jane Austen" };
        books.Add(new Book("978-0-1404-3426-2", "Pride and Prejudice",
            book3Authors, new DateTime(1813, 1, 28), 19.99m));

        GeneralDel<Book, string> del;
        del = BookFunctions.GetAuthors;

        LibraryEngine.ProcessBooks(books, del);
        Console.WriteLine();
        LibraryEngine.ProcessBooks(books, BookFunctions.GetTitle);
        Console.WriteLine();
        LibraryEngine.ProcessBooksWithFunc(books, BookFunctions.GetPrice);
        Console.WriteLine();
        LibraryEngine.ProcessBooksWithFunc(books, delegate (Book B) { return B.ISBN; });
        Console.WriteLine();
        LibraryEngine.ProcessBooks(books, B => B.PublicationDate.ToString()); 
        Console.WriteLine();
    }
}