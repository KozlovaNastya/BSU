using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Web;
using WcfService.Models;

namespace WcfService
{
    [ServiceContract]
    public interface IPlayerService
    {
        [OperationContract]
        [WebGet(UriTemplate = "players", ResponseFormat = WebMessageFormat.Json)]
        List<Player> GetAll();

        [OperationContract]
        [WebGet(UriTemplate = "players/position/{position}", ResponseFormat = WebMessageFormat.Json)]
        List<Player> GetByPosition(string position);

        [OperationContract]
        [WebGet(UriTemplate = "players/{id}", ResponseFormat = WebMessageFormat.Json)]
        Player GetById(string id);

        [OperationContract]
        [WebInvoke(Method = "POST", UriTemplate = "players", RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)]
        void Insert(Player player);

        [OperationContract]
        [WebInvoke(Method = "PUT", UriTemplate = "players", RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json)]
        void Update(Player player);

        [OperationContract]
        [WebInvoke(Method = "DELETE", UriTemplate = "players/{id}", ResponseFormat = WebMessageFormat.Json)]
        void Delete(string id);
    }
}