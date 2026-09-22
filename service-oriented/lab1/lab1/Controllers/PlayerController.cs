using Microsoft.AspNetCore.Mvc;
using lab1.Models;
using lab1.Services;

namespace lab1.Controllers
{
    public class PlayerController : Controller
    {
        private readonly PlayerService _service;

        public PlayerController(PlayerService service)
        {
            _service = service;
        }

        // GET: /Players
        public IActionResult Index(string? position)
        {
            List<Player> list;
            if (string.IsNullOrWhiteSpace(position))
                list = _service.GetAll();
            else
                list = _service.GetByPosition(position);

            ViewBag.Position = position;
            return View(list);
        }

        // GET: /Players/Details/adarmlem
        public IActionResult Details(string id)
        {
            var player = _service.GetById(id);
            if (player == null) return NotFound();
            return View(player);
        }

        // GET: /Players/Create
        public IActionResult Create() => View();

        // POST: /Players/Create
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Create(Player player)
        {
            if (!ModelState.IsValid) return View(player);
            try
            {
                _service.Insert(player);
                return RedirectToAction(nameof(Index));
            }
            catch (Exception ex)
            {
                ModelState.AddModelError("", "Ошибка при добавлении: " + ex.Message);
                return View(player);
            }
        }

        // GET: /Players/Edit/adarmlem
        public IActionResult Edit(string id)
        {
            var player = _service.GetById(id);
            if (player == null) return NotFound();
            return View(player);
        }

        // POST: /Players/Edit/adarmlem
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Edit(string id, string newFname)
        {
            try
            {
                _service.UpdateFname(id, newFname);
                return RedirectToAction(nameof(Index));
            }
            catch (Exception ex)
            {
                ModelState.AddModelError("", "Ошибка при изменении: " + ex.Message);
                var player = _service.GetById(id);
                return View(player);
            }
        }

        // GET: /Players/Delete/adarmlem
        public IActionResult Delete(string id)
        {
            var player = _service.GetById(id);
            if (player == null) return NotFound();
            return View(player);
        }

        // POST: /Players/Delete/adarmlem
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public IActionResult DeleteConfirmed(string id)
        {
            try
            {
                _service.Delete(id);
                return RedirectToAction(nameof(Index));
            }
            catch (Exception ex)
            {
                ModelState.AddModelError("", "Ошибка при удалении: " + ex.Message);
                return RedirectToAction(nameof(Index));
            }
        }
    }
}