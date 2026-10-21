using System;
using System.Collections.Generic;
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

        // GET: /Player
        public IActionResult Index(string position)
        {
            List<Player> list;
            if (string.IsNullOrWhiteSpace(position))
                list = _service.GetAll();
            else
                list = _service.GetByPosition(position);

            ViewBag.Position = position;
            return View(list);
        }

        // GET: /Player/Details/adarmlem
        public IActionResult Details(string id)
        {
            var player = _service.GetById(id);
            if (player == null) return NotFound();
            return View(player);
        }

        // GET: /Player/Create
        public IActionResult Create() => View();

        // POST: /Player/Create
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

        // GET: /Player/Edit/adarmlem
        public IActionResult Edit(string id)
        {
            var player = _service.GetById(id);
            if (player == null) return NotFound();
            return View(player);
        }

        // POST: /Player/Edit/adarmlem
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Edit(Player player)
        {
            if (!ModelState.IsValid) return View(player);
            try
            {
                _service.Update(player);
                return RedirectToAction(nameof(Index));
            }
            catch (Exception ex)
            {
                ModelState.AddModelError("", "Ошибка при изменении: " + ex.Message);
                return View(player);
            }
        }

        // GET: /Player/Delete/adarmlem
        public IActionResult Delete(string id)
        {
            var player = _service.GetById(id);
            if (player == null) return NotFound();
            return View(player);
        }

        // POST: /Player/Delete/adarmlem
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